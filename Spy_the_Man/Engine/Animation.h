/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Animation.h
Project: CS200
Author: Sangbeom Kim
-----------------------------------------------------------------*/
#pragma once
#include <vector>
#include <string>

namespace PM {
	class Animation {
	public:
		Animation();
		Animation(std::string fileName, int animnum);
		~Animation();
		void Update(double dt);
		int GetDisplayFrame();
		void ResetAnimation();
		bool IsAnimationDone();
	private:
		enum class Command {
			PlayFrame,
			Loop,
			End
		};
		class CommandData {
		public:
			virtual ~CommandData(){}
			virtual Command GetType() = 0;
		};

		class PlayFrame : public CommandData {
		public:
			PlayFrame(int frame, double duration);
			virtual Command GetType() override { return Command::PlayFrame; }
			void Update(double dt);
			bool IsFrameDone();
			void ResetTime();
			int GetFrameNum();
		private:
			int frame;
			double targetTime;
			double timer;
		};
		class Loop : public CommandData {
		public:
			Loop(int loopToIndex);
			virtual Command GetType() override { return Command::Loop; }
			int GetLoopToIndex();
		private:
			int loopToIndex;
		};
		class End : public CommandData {
		public:
			virtual Command GetType() override { return Command::End; }
		private:
		};

		bool isAnimationDone;
		int animSequenceIndex;
		PlayFrame* currPlayFrameData;
		std::vector<CommandData*> animation;
	};
}
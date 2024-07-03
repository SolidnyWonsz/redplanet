#pragma once

typedef int PID;

namespace Tasking {
    class Task {
        public:
            Task();
            ~Task();

            void ElevatePrivilages();
            void Kill();
        private:
            PID pid; 
    };

    namespace Scheduler {
        void Initialize();
        void Schedule();
    }
}
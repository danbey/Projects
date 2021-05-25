#include <iostream>
#include <queue>
#include <mutex>
#include <algorithm>
#include <thread>
#include <chrono>
#include <condition_variable>

std::mutex mt;
std::mutex mt_count;
std::queue<int> q;
//std::condition_variable condvar_;

static uint32_t count = 0;

#if 0
void consumer()
{ 
    int g;
    while (1) {
        //consume and pop from queue
        mt.lock();
        if (!q.empty()) {
            std::cout << q.front() << std::endl;
            q.pop();
        }
        mt.unlock();
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

void producer()
{
    while (1) {
        //produce push to queue
        mt.lock();
        if (q.size() != 20) {
            int num = std::rand();
            std::cout << "pushing: " << num << std::endl;
            q.push(num);
        }
        mt.unlock();
    }
}
#endif

static int wcnt=0;
static int rcnt=0;
static int wwait=0;
static int rwait=0;
std::condition_variable cond_reader;
std::condition_variable cond_writer;
std::mutex mtx;

void reader()
{
    std::unique_lock<std::mutex> mt(mtx, std::defer_lock);
    while (1)
    {
        for (int idx=0;idx < 10; idx++) {
            mt.lock();
            if (rcnt == -1) {
                cond_reader.wait(mt);
            }
            rcnt++;
            mt.unlock();
            

            std::cout << "reading from file:"  << idx << std::endl;
            
            mt.lock();
            rcnt--;
            if (rcnt == 0) 
                cond_writer.notify_all();

            mt.unlock();
        }
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

void writer()
{
    std::unique_lock<std::mutex> mt(mtx, std::defer_lock);
    while (1)
    {
        mt.lock();
        if (rcnt > 0) {
            cond_writer.wait(mt);
        }
        rcnt = -1;
        mt.unlock();

        std::cout << "******writing to file" << std::endl;
        
        mt.lock();
        rcnt=0;
        cond_reader.notify_all();
        cond_writer.notify_all();
        mt.unlock();

        std::this_thread::sleep_for(std::chrono::seconds(2));
    }    
}

int main()
{

    std::thread tr1(writer);
    std::thread tr2(reader);

    tr1.join();
    tr2.join();

   return 0;
}
// Challenge Code 2 - Andrew Barlow - MTE 140 - Due March 11th

#include <iostream>
#include <string>
#include <array>
#include <chrono>
using namespace std;

class CircularQueue
{
public:
    static const int EMPTY_QUEUE;
    CircularQueue();
    CircularQueue(unsigned int capacity);
    ~CircularQueue();
    bool enqueue(int value);
    int dequeue();
    int peek() const;
    bool empty() const;
    bool full() const;
    int size() const;
    void print() const;
    void increment();
private:
    int *items_;
    int head_, tail_;
    int capacity_;
    int size_;
};


const int CircularQueue::EMPTY_QUEUE = -999;

CircularQueue::CircularQueue()
{
	capacity_ = 16;
	size_ = 0;
	head_ = -1;
	tail_ = -1;
	items_ = new int[capacity_];
}

CircularQueue::CircularQueue(unsigned int capacity)
{
	capacity_ = capacity;
	size_ = 0;
	head_ = -1;
	tail_ = -1;
	items_ = new int[capacity_];
}

CircularQueue::~CircularQueue()
{
	delete [] items_;
	head_ =-1;
	tail_ = -1;
}

bool CircularQueue::empty() const
{
	return size_ == 0;
}

bool CircularQueue::full() const
{
	return size_ == capacity_;
}

int CircularQueue::size() const
{
	return size_;
}

bool CircularQueue::enqueue(int value)
{
	if(head_ == -1 && tail_ == -1)
	{
		head_ = tail_ = 0;
		items_[tail_] = value;
		size_++;
		return true;
	}
	else if(full())
		return false;
	else
	{
		size_++;
		tail_ = (tail_ + 1) % capacity_;
		items_[tail_] = value;
		return true;
	}
}

int CircularQueue::dequeue()
{
	if(empty())
		return EMPTY_QUEUE;
	else
	{
		int value = items_[head_];
		head_ = (head_ + 1) % capacity_;
		size_--;
		return value;
	}
}

int CircularQueue::peek() const
{
	if(empty())
		return EMPTY_QUEUE;
	return items_[head_];
}

void CircularQueue::print() const
{
	for(int i = head_; i < head_ + size_; i++)
		cout << "Item number: " << i - head_ << " = " << items_[i % capacity_] << endl;
}

void CircularQueue::increment()
{
	head_ = (head_ + 1) % capacity_;
	tail_ = (tail_ + 1) % capacity_;
}

void arraySetup(CircularQueue & newArray, int array[], int N)
{
	for(int i = 0; i < N; i++)
		newArray.enqueue(array[i]);
}


int ramen_challenge(int R, int K, int N, CircularQueue & lineUp)
{
	int profit = 0, atBar = 0, currentGroup = 0, personLimit = 0;

	for(int i = 0; i < R; i++)
	{
		atBar = 0, currentGroup = 0, personLimit = 0;
		while(atBar + lineUp.peek() <= K && personLimit < N)
		{
			currentGroup = lineUp.peek();
			atBar += currentGroup;
			lineUp.increment();
			personLimit++;
		}
		profit += atBar;
	}
	return profit;
}


int main()
{
	// R = number of times Ramen is served
	// K = number of people that the bar can hold
	// N = number of people in the array

	int K = 0, R = 0, N = 0;

	// Test 1: Expected output: 21
	int toLineUpI[] = {1, 4, 2, 1};
	N = 4;
	R = 4;
	K = 6;
	CircularQueue newQueueI(N);
	arraySetup(newQueueI, toLineUpI, N);
	cout << "Test 1: " << ramen_challenge(R, K, N, newQueueI) << endl;


	// Test 2: Expected output: 100
	int toLineUpII[] = {1};
	N = 1, R = 100, K = 10;
	CircularQueue newQueueII(N);
	arraySetup(newQueueII, toLineUpII, N);
	cout << "Test 2: " << ramen_challenge(R, K, N, newQueueII) << endl;


	// Test 3: Expected output: 20
	int toLineUpIII[] = {2,4,2,3,4,2,1,2,1,3};
	N = 10, R = 5, K = 5;
	CircularQueue newQueueIII(N);
	arraySetup(newQueueIII, toLineUpIII, N);
	cout << "Test 3: " << ramen_challenge(R, K, N, newQueueIII) << endl;


	// Test 4: Expected output: 150000000
	auto start = chrono::high_resolution_clock::now(); // timer start
	int toLineUpIV[] = {1,2};
	N = 2, R = 100000000, K = 2;
	CircularQueue newQueueIV(N);
	arraySetup(newQueueIV, toLineUpIV, N);
	cout << "Test 4: " << ramen_challenge(R, K, N, newQueueIV) << endl;
	auto finish = chrono::high_resolution_clock::now(); //timer stop
	chrono::duration<double> elapsed = finish - start;
	cout << "Elapsed time: " << elapsed.count() << endl;


	// Test 5: Expected output: 176000000
	start = chrono::high_resolution_clock::now(); // timer start
	int toLineUpV[] = {43,34,39,11,22,35,46,59,16,13,34};
	N = 11, R = 1000000, K = 200;
	CircularQueue newQueueV(N);
	arraySetup(newQueueV, toLineUpV, N);
	cout << "Test 5: " << ramen_challenge(R, K, N, newQueueV) << endl;
	finish = chrono::high_resolution_clock::now(); //timer stop
	elapsed = finish - start;
	cout << "Elapsed time: " << elapsed.count() << endl;
}


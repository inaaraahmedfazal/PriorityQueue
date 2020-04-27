// Inaara Ahmed-Fazal   20821562
// Kayla Jetha          20822795
// Meghan LaCoste       20845775

#include <iostream>
#include "lab3_priority_queue.hpp"

using namespace std;

// PURPOSE: Parametric constructor 
// initializes heap to an array of (n_capacity + 1) elements
PriorityQueue::PriorityQueue(unsigned int n_capacity) {
	heap = new TaskItem*[n_capacity + 1];
	capacity = n_capacity;
	size = 0;
}

// PURPOSE: Explicit destructor of the class PriorityQueue
PriorityQueue::~PriorityQueue() {
	for(int index = 1; index <= size; index++) {
		if(heap[index]) // optional
			delete heap[index];
		heap[index] = NULL;
	}
}

// PURPOSE: Returns the number of elements in the priority queue
unsigned int PriorityQueue::get_size() const {
	return size;
}

// PURPOSE: Returns true if the priority queue is empty; false, otherwise
bool PriorityQueue::empty() const {
	if(size == 0) return true;
	return false;
}

// PURPOSE: Returns true if the priority queue is full; false, otherwise
bool PriorityQueue::full() const {
	if(size == capacity) return true;
	return false;
}

// PURPOSE: Prints the contents of the priority queue; format not specified
void PriorityQueue::print() const {
	for( int i = 1; i <= size; ++i){
		cout << "TaskItem " << i << endl;
		cout << "Priority: " << heap[i] -> priority << endl;
		cout << "Description: " << heap[i] -> description << endl;
		cout << endl;
	}
}

// PURPOSE: Returns the max element of the priority queue without removing it
// if the priority queue is empty, it returns (-1, "N/A")
PriorityQueue::TaskItem PriorityQueue::max() const {
	if(size > 0) return TaskItem(*heap[1]);
	return TaskItem(-1, "NULL");
}

// PURPOSE: Inserts the given value into the priority queue
// re-arranges the elements back into a heap
// returns true if successful and false otherwise
// priority queue does not change in capacity

//COPY FROM LECTURE 8
bool PriorityQueue::enqueue( TaskItem val ) {
	
	// if the heap is already full, no more can be added
	if (size == capacity) return false;
	
	// case for empty heap
	if (size == 0) {
		heap [1] = new TaskItem (val);
		size++;
		return true;
	}

	// general case: non-empty heap
	int i = size + 1;
	heap [i] = new TaskItem (val);
	while (i > 1 && heap [i/2] -> priority < heap[i] -> priority) 
	{
		TaskItem* temp = heap[i];
		heap[i] = heap [i/2];
		heap [i/2] = temp;
		i/=2;
	}
	size ++;
	return true;
}

// PURPOSE: Removes the top element with the maximum priority
// re-arranges the remaining elements back into a heap
// returns true if successful and false otherwise
// priority queue does not change in capacity

//if/else for which is bigger, then swap if needed?
//swap root with last value, remove last value, then propagate that new root down
bool PriorityQueue::dequeue() {
	if(size == 0) return false;
	
	//swap first and last
	TaskItem* temp = heap[1];
	heap[1] = heap[size];
	heap[size] = temp;
	
	//free up memory of TaskItem being dequeued
	delete heap[size];
	heap[size] = NULL;
	
	int i = 1;
	bool place_found = false;
	
	//find place for TaskItem that has been switched to heap[1]
	while(i < size && !place_found) {
		if(2*i < size && 2*i + 1 < size) {
			if(heap[i] > heap[2*i] && heap [i] > heap[2*i + 1]) place_found = true;
			else if(heap[2*i] > heap[2*i + 1]) {
				temp = heap[2*i];
				heap[2*i] = heap[i];
				heap[i] = temp;
				i *= 2;
			}
			else {
				temp = heap[2*i];
				heap[2*i] = heap[i];
				heap[i] = temp;
				i = 2*i + 1;
			}
		}
		else if (2*i < size) {
			if(heap[i] > heap[2*i]) place_found = true;
			else {
				temp = heap[2*i];
				heap[2*i] = heap[i];
				heap[i] = temp;
				i = 2*i + 1;
			}
		}
		else place_found = true;
	}
	size--;
	return true;
}

// Your name here: Aarush Tippa
// Your NetID here:at1407
//
// IMPORTANT NOTE:
// In your submission, you are only allowed to make modifications where it is indicated, 
// and you must provide your implementation in those designated areas. 
// You are not permitted to make changes to the code in any other location.
//
#ifndef HW2B_H
#define HW2B_H

#include <vector>
#include <stdexcept>

class Event {
public:
    int location_id;
    int event_id;
    int timestamp;
    std::string detail;

    Event(int location_id, int event_id, int timestamp, const std::string& text)
        : location_id(location_id), event_id(event_id), timestamp(timestamp), detail(text) {}

    bool operator<(const Event& other) const {
        return timestamp < other.timestamp; 
    }
    
    bool operator>(const Event& other) const {
        return timestamp > other.timestamp; 
    }
    
    friend std::ostream& operator<< (std::ostream& out, const Event& e) ;
};

std::ostream& operator<< (std::ostream& out, const Event& e) {
    out << e.location_id << "," << e.event_id << "," << e.timestamp << "," << e.detail ;
    return out;
}


template <typename T>
class MinHeap {
private:
    std::vector<T> heap;


    int calcParent(int i) {
        return (i - 1) / 2;
    }
    int calcLeft(int i) {
        return 2 * i + 1;
    }
    int calcRight(int i) {
        return 2 * i + 2;

    }

    void minHeapify(int i) {
        // Provide your implementation here
        int left = calcLeft(i);
        int right = calcRight(i);
        int heap_size = heap.size() - 1;
        int smallest;

        if (left <= (heap_size)  & heap[left] < heap[i]) {
             smallest = left;}
        else {
             smallest = i;
        }

        if(right <= (heap_size) & heap[right] < heap[smallest]) {
            smallest = right;
        }
        if (smallest != i) {
            std::swap(heap[i], heap[smallest]);
            minHeapify(smallest);


        }


        // End of your implementation
    }


public:
    MinHeap() {}

    MinHeap(const std::vector<T>& arr) {
        heap = arr;
        int n = heap.size();
        for (int i =n / 2 - 1; i >= 0; i--) {
            minHeapify(i);
        }
    }

    void insert(const T& value) {
        // Provide your implementation here
        heap.push_back(value);
        int n = heap.size() - 1;

        while (n>0 and heap[calcParent(n)] > heap[n]) {
            std::swap(heap[n], heap[calcParent(n)]);
            n = calcParent(n);
        }
        // End of your implementation
    }

    T getMin() {
        if (!isEmpty()) {
            return heap[0];
        }
        throw std::runtime_error("Heap is empty.");
    }

    T extractMin() {
        if (isEmpty()) {
            throw std::runtime_error("Heap is empty.");
        }

        // Provide your implementation here
        // Don't forget to return the extracted Min item
        int heapSize = heap.size() -1;

        T min = getMin();
        heap[0] = heap[heapSize];
        heap.pop_back();
        minHeapify(0);
        return min;
        // End of your implementation
    }

    bool isEmpty() {
        return heap.empty();
    }
};

std::vector<Event> getFirstNEvents(std::vector<std::vector<Event>>& all_events, int n) {
    std::vector<Event> first_n_events;
    MinHeap<Event> min_heap;

    // Provide your implementation here
    for(int i = 0; i < all_events.size(); i++) {
        for (int j = 0; j < all_events[i].size(); j++) {
            min_heap.insert(all_events[i][j]);
        }
    }
    for(int i = 0; i < n; i++) {
        first_n_events.push_back(min_heap.extractMin());
    }

    // End of your implementation
    
    return first_n_events;
}

#endif // HW2B_H

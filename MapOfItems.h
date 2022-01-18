#ifndef MAPOFITEMS_H
#define MAPOFITEMS_H

#include "Item.h"
#include <vector>
using std::vector;

// TODO: your code goes here
class MapOfItems {
private:
	vector<Item> items;
public:
	void addItem(Item item){
		items.push_back(item);
	}
	int size() const{
		return items.size();
	}
	const vector<Item>& getItems() const{
		return items;
	}
	vector<Item*> getTour(double walkingSpeed)  {
		int endTime = 3600;
		double speed = walkingSpeed;
		int firstIndex = first(endTime);
		Item location  = items[firstIndex];
		vector <Item*> tour ;
		tour.push_back(&items[firstIndex]);
		int currentTime = location.getAvailableTime();
		Item target(0,0,"0",endTime);
		while (currentTime < endTime){
			int targetIndex = findTargetIndex(location, currentTime, speed, endTime, tour);
			if (targetIndex == -1){
				break;
			}
			currentTime += location.distanceTo(items[targetIndex])/speed;
			location = items[targetIndex];
			if (tooEarly(location, currentTime)){
				currentTime = location.getAvailableTime();
			}
			tour.push_back(&items[targetIndex]);

		}
		return tour;
	}
private:
	int first(int endTime) const{
		int earliestTime = endTime;
		int index = 0;
		Item firstAvailable(0,0,"0",0);
		for (int i = 0; i < size(); i++){
			if (items[i].getAvailableTime() < earliestTime){
				earliestTime = items[i].getAvailableTime();
				firstAvailable = items[i];
				index = i;
			}
		}
		return index;
	}
	int findArrivalTime (Item location, Item target, int currentTime, double speed) const{
		return currentTime + location.distanceTo(target)/speed;
	}

	bool tooEarly (Item item, int time) const{
		if (time < item.getAvailableTime()){
			return true;
		}
		return false;
	}
	bool isAvailable (Item item, int time, int endTime) const{
		if ( time > item.getAvailableTime() + 900){
			return false;
		}
		if (item.getAvailableTime() >= endTime){
			return false;
		}
		return true;
	}
	bool alreadyVisited(Item item, vector <Item*> visited) const{
		for (int i = 0; i < visited.size(); i++){
			Item* visitedItem = visited[i];
			if (visitedItem->getID() == item.getID()){
				return true;
			}
		}
		return false;
	}
	int findTargetIndex (Item location, int time, double speed, int endTime, vector <Item*> visited) const{
		Item target(0,0,"0",endTime);
		int quickestJourney = endTime;
		int index = -1;
		for (int i = 0; i < size(); i++){
			Item item = items[i];
			int arrivalTime = findArrivalTime(location,item, time, speed);
			if (tooEarly(item, arrivalTime)){
				arrivalTime = item.getAvailableTime();
			}
			if (isAvailable(item, arrivalTime, endTime)
					&& (arrivalTime < quickestJourney)
					&& !alreadyVisited(item, visited)
			){
				target = item;
				quickestJourney = arrivalTime;
				index = i;
			}
		}
		return index;
	}
};



// don't write any code below this line

#endif


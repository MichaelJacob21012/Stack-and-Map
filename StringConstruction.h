#ifndef STRINGCONSTRUCTION_H
#define STRINGCONSTRUCTION_H

#include <string>
using std::string;

/**
 * return the longest section at the start of remaining
 * that is contained within build
 */
const string findClone(string remaining, string build){
	for (int i = (remaining.length()); i > 0; i--){
		string cloneSegment = remaining.substr(0,i);
		int posCloneSegment = build.find(cloneSegment);
		if (posCloneSegment != -1){
			return cloneSegment;
		}
	}
	return "";
}

const int stringConstruction(string  target, int appendCost, int cloneCost ){
	int cheapestCost = 0;
	bool cloneWorthy = true;
	string remaining = target;
	string build = "";
	while(build != target){
		cloneWorthy = true;
		string cloneCandidate = findClone(remaining,build);
		int cLength = cloneCandidate.length();
		if (cloneCandidate == ""){
			cloneWorthy = false;
		}
		// check for longer overlapping clone candidates
		if (cLength > 1){
			for (int i = cLength; i > 1; i--){
				if(i-1 + i > remaining.length()){
					break;
				}
				if (build.find(remaining.substr(i-1,2*cLength +1 -i)) != -1){
					cloneCandidate.erase(cLength-1,1);
					cLength--;
					break;
				}
			}
		}
		if (cLength*appendCost < cloneCost){
			cloneWorthy = false;
		}

		if (cloneWorthy == true){
			build += cloneCandidate;
			remaining.erase(0,cloneCandidate.length());
			cheapestCost += cloneCost;
		}
		else {
			build += remaining[0];
			remaining.erase(0,1);
			cheapestCost += appendCost;
		}
	}
	return cheapestCost;
}


// do not write or edit anything below this line

#endif


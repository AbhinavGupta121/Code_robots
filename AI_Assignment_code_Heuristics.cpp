#include <bits/stdc++.h>
using namespace std;
struct box{
	int dest_x{};
	int dest_y{};
	int x{};
	int y{};
	bool picked{false};
};
struct robot{
	int final_x{};
	int final_y{};
	int x{};
	int y{};
	bool item{false};
	int ind{-1};
	box bocs{};
	int g{};
	int h{};
};
struct robots{
	int time_step{};
	robot rob[10];
	int mat[10][10];
	box task[10];
	int g{};
	int f{};
	int h{};
};

robots pickup(robots robo, int j, int i);
robots drop(robots robo, int j);
robots down(robots robo, int j, int n);
robots up(robots robo, int j);
robots right(robots robo, int j, int m);
robots left(robots robo, int j);
robots stay(robots robo);
void combinations(robots robo, int y, int n, int m, queue <robots> *q, int t);
bool goal(robots robo, int r, int t);

robots pickup(robots robo, int j, int i){
	if (robo.task[i].x == robo.rob[j].x && robo.task[i].y == robo.rob[j].y && !robo.task[i].picked && robo.mat[robo.rob[j].x][robo.rob[j].y] == -4 && !robo.rob[j].item){
		robo.rob[j].item = true;
		robo.rob[j].bocs = robo.task[i];
		robo.rob[j].ind = i;
		robo.task[i].picked = true;
	}
	return robo;
}
robots drop(robots robo, int j){
	if (robo.mat[robo.rob[j].x][robo.rob[j].y] == -4 && robo.rob[j].item){
		robo.rob[j].item = false;
		robo.rob[j].ind = -1;
	}
	return robo;
}
robots down(robots robo, int j, int n){
	if (robo.rob[j].x + 1 < n && robo.mat[robo.rob[j].x + 1][robo.rob[j].y] != -2 && robo.mat[robo.rob[j].x + 1][robo.rob[j].y] != -3){
		
		if (robo.mat[robo.rob[j].x + 1][robo.rob[j].y] == 0){
			robo.mat[robo.rob[j].x + 1][robo.rob[j].y] = -3;
		}
		if (robo.mat[robo.rob[j].x][robo.rob[j].y] == -3){
			robo.mat[robo.rob[j].x][robo.rob[j].y] = 0;
		}
		if (robo.rob[j].item){
			robo.rob[j].bocs.x++;
			robo.task[robo.rob[j].ind].x++;
		}
		robo.rob[j].x++;
		return robo;
	}
	return robo;
}
robots up(robots robo, int j){
	if (robo.rob[j].x - 1 >= 0 && robo.mat[robo.rob[j].x - 1][robo.rob[j].y] != -2 && robo.mat[robo.rob[j].x - 1][robo.rob[j].y] != -3){
		
		if (robo.mat[robo.rob[j].x - 1][robo.rob[j].y] == 0){
			robo.mat[robo.rob[j].x - 1][robo.rob[j].y] = -3;
		}
		if (robo.mat[robo.rob[j].x][robo.rob[j].y] == -3){
			robo.mat[robo.rob[j].x][robo.rob[j].y] = 0;
		}
		if (robo.rob[j].item){
			robo.rob[j].bocs.x--;
			robo.task[robo.rob[j].ind].x--;
		}
		robo.rob[j].x--;
		return robo;
	}
	return robo;
}
robots right(robots robo, int j, int m){
	if (robo.rob[j].y + 1 < m && robo.mat[robo.rob[j].x][robo.rob[j].y + 1] != -2 && robo.mat[robo.rob[j].x][robo.rob[j].y + 1] != -3){
		
		if (robo.mat[robo.rob[j].x][robo.rob[j].y + 1] == 0){
			robo.mat[robo.rob[j].x][robo.rob[j].y + 1] = -3;
		}
		if (robo.mat[robo.rob[j].x][robo.rob[j].y] == -3){
			robo.mat[robo.rob[j].x][robo.rob[j].y] = 0;
		}
		if (robo.rob[j].item){
			robo.rob[j].bocs.y++;
			robo.task[robo.rob[j].ind].y++;
		}
		robo.rob[j].y++;
		return robo;
	}
	return robo;
}
robots left(robots robo, int j){
	if (robo.rob[j].y - 1 >= 0 && robo.mat[robo.rob[j].x][robo.rob[j].y - 1] != -2 && robo.mat[robo.rob[j].x][robo.rob[j].y - 1] != -3){
		
		if (robo.mat[robo.rob[j].x][robo.rob[j].y - 1] == 0){
			robo.mat[robo.rob[j].x][robo.rob[j].y - 1] = -3;
		}
		if (robo.mat[robo.rob[j].x][robo.rob[j].y] == -3){
			robo.mat[robo.rob[j].x][robo.rob[j].y] = 0;
		}
		if (robo.rob[j].item){
			robo.rob[j].bocs.y--;
			robo.task[robo.rob[j].ind].y--;
		}
		robo.rob[j].y--;
		return robo;
	}
	return robo;
}
robots stay(robots robo){
	
	return robo;
}
bool compare_structs(robots robo1, robots robo2, int r, int t){
	for (int i{};i<r;i++){
		if (robo1.rob[i].x == robo2.rob[i].x && robo1.rob[i].y == robo2.rob[i].y){
			continue;
		}else{
			return false;
		}
	}
	for (int j{};j<t;j++){
		if (robo1.task[j].x == robo2.task[j].x && robo1.task[j].y == robo2.task[j].y){
			continue;
		}else{
			return false;
		}
	}
	return true;
}
void combinations(robots robo, int y, int n, int m, vector <robots> *q, int t, int r){
	if (y + 1 == r){
		robo.time_step++;
	}
	if (y == 0){
		robots robo1;
		if(robo.rob[y].x + 1 < n && robo.mat[robo.rob[y].x + 1][robo.rob[y].y] != -2 && robo.mat[robo.rob[y].x + 1][robo.rob[y].y] != -3){
			
			robo1 = down(robo, y, n);
			robo1.h = 0;
			for (int k{};k<r;k++){
				if (robo1.h < abs(robo1.rob[k].x - robo1.rob[k].final_x) + abs(robo1.rob[k].y - robo1.rob[k].final_y)){
					robo1.h = abs(robo1.rob[k].x - robo1.rob[k].final_x) + abs(robo1.rob[k].y - robo1.rob[k].final_y);
				}
			}
			robo1.g++;
			robo1.f = robo1.g + robo1.h;
			int k{};
			while (k<q -> size()){
				if (compare_structs(robo1, q -> at(k), r, t)){
					break;
				}
				k++;
			}
			if (k >= q -> size()){
				k = 0;
				if (q -> size() > 0){
    				while (k < q -> size()){
    				    if(q -> at(k).f > robo1.f){
    					k++;
    				    }else{
    				        break;
    				    }
    				}
    				q -> insert(q -> begin() + k,robo1);
				}else{
				    q -> insert(q -> begin(),robo1);
				}
			}else{
				if (q -> at(k).g > robo1.g){
					q -> at(k) = robo1;
				}
			}
			if (robo.mat[robo.rob[y].x][robo.rob[y].y] == -4 && !robo.rob[y].item){				
				for (int i{};i<t;i++){
					if (robo.task[i].x == robo.rob[y].x && robo.task[i].y == robo.rob[y].y && !robo.task[i].picked ){
						robo1 = pickup(robo, y, i);
						robo1 = down(robo1, y, n);
robo1.h = 0;
						for (int k{};k<r;k++){
				if (robo1.h < abs(robo1.rob[k].x - robo1.rob[k].final_x) + abs(robo1.rob[k].y - robo1.rob[k].final_y)){
					robo1.h = abs(robo1.rob[k].x - robo1.rob[k].final_x) + abs(robo1.rob[k].y - robo1.rob[k].final_y);
				}
			}
			robo1.g++;
			robo1.f = robo1.g + robo1.h;
			int k{};
			while (k<q -> size()){
				if (compare_structs(robo1, q -> at(k), r, t)){
					break;
				}
				k++;
			}
			if (k >= q -> size()){
				k = 0;
				if (q -> size() > 0){
    				while (k < q -> size()){
    				    if(q -> at(k).f > robo1.f){
    					k++;
    				    }else{
    				        break;
    				    }
    				}
    				q -> insert(q -> begin() + k,robo1);
				}else{
				    q -> insert(q -> begin(),robo1);
				}
			}else{
				if (q -> at(k).g > robo1.g){
					q -> at(k) = robo1;
				}
			}
					}
				}
			}
			if (robo.mat[robo.rob[y].x][robo.rob[y].y] == -4 && robo.rob[y].item){
				robo1 = drop(robo, y);
				robo1 = down(robo1, y, n);
robo1.h = 0;
				for (int k{};k<r;k++){
				if (robo1.h < abs(robo1.rob[k].x - robo1.rob[k].final_x) + abs(robo1.rob[k].y - robo1.rob[k].final_y)){
					robo1.h = abs(robo1.rob[k].x - robo1.rob[k].final_x) + abs(robo1.rob[k].y - robo1.rob[k].final_y);
				}
			}
			robo1.g++;
			robo1.f = robo1.g + robo1.h;
			int k{};
			while (k<q -> size()){
				if (compare_structs(robo1, q -> at(k), r, t)){
					break;
				}
				k++;
			}
			if (k >= q -> size()){
				k = 0;
				if (q -> size() > 0){
    				while (k < q -> size()){
    				    if(q -> at(k).f > robo1.f){
    					k++;
    				    }else{
    				        break;
    				    }
    				}
    				q -> insert(q -> begin() + k,robo1);
				}else{
				    q -> insert(q -> begin(),robo1);
				}
			}else{
				if (q -> at(k).g > robo1.g){
					q -> at(k) = robo1;
				}
			}
			}
		}
		
		if(robo.rob[y].x - 1 >= 0 && robo.mat[robo.rob[y].x - 1][robo.rob[y].y] != -2 && robo.mat[robo.rob[y].x - 1][robo.rob[y].y] != -3){
		robo1 = up(robo, y);
robo1.h = 0;
		for (int k{};k<r;k++){
				if (robo1.h < abs(robo1.rob[k].x - robo1.rob[k].final_x) + abs(robo1.rob[k].y - robo1.rob[k].final_y)){
					robo1.h = abs(robo1.rob[k].x - robo1.rob[k].final_x) + abs(robo1.rob[k].y - robo1.rob[k].final_y);
				}
			}
			robo1.g++;
			robo1.f = robo1.g + robo1.h;
			int k{};
			while (k<q -> size()){
				if (compare_structs(robo1, q -> at(k), r, t)){
					break;
				}
				k++;
			}
			if (k >= q -> size()){
				k = 0;
				if (q -> size() > 0){
    				while (k < q -> size()){
    				    if(q -> at(k).f > robo1.f){
    					k++;
    				    }else{
    				        break;
    				    }
    				}
    				q -> insert(q -> begin() + k,robo1);
				}else{
				    q -> insert(q -> begin(),robo1);
				}
			}else{
				if (q -> at(k).g > robo1.g){
					q -> at(k) = robo1;
				}
			}
		if (robo.mat[robo.rob[y].x][robo.rob[y].y] == -4 && !robo.rob[y].item){
		for (int i{};i<t;i++){
			if (robo.task[i].x == robo.rob[y].x && robo.task[i].y == robo.rob[y].y && !robo.task[i].picked ){
			robo1 = pickup(robo, y, i);
			robo1 = up(robo1, y);
robo1.h = 0;
			for (int k{};k<r;k++){
				if (robo1.h < abs(robo1.rob[k].x - robo1.rob[k].final_x) + abs(robo1.rob[k].y - robo1.rob[k].final_y)){
					robo1.h = abs(robo1.rob[k].x - robo1.rob[k].final_x) + abs(robo1.rob[k].y - robo1.rob[k].final_y);
				}
			}
			robo1.g++;
			robo1.f = robo1.g + robo1.h;
			int k{};
			while (k<q -> size()){
				if (compare_structs(robo1, q -> at(k), r, t)){
					break;
				}
				k++;
			}
			if (k >= q -> size()){
				k = 0;
				if (q -> size() > 0){
    				while (k < q -> size()){
    				    if(q -> at(k).f > robo1.f){
    					k++;
    				    }else{
    				        break;
    				    }
    				}
    				q -> insert(q -> begin() + k,robo1);
				}else{
				    q -> insert(q -> begin(),robo1);
				}
			}else{
				if (q -> at(k).g > robo1.g){
					q -> at(k) = robo1;
				}
			}
		}
		}
		}
		if (robo.mat[robo.rob[y].x][robo.rob[y].y] == -4 && robo.rob[y].item){
		robo1 = drop(robo, y);
		robo1 = up(robo1, y);
robo1.h = 0;
		for (int k{};k<r;k++){
				if (robo1.h < abs(robo1.rob[k].x - robo1.rob[k].final_x) + abs(robo1.rob[k].y - robo1.rob[k].final_y)){
					robo1.h = abs(robo1.rob[k].x - robo1.rob[k].final_x) + abs(robo1.rob[k].y - robo1.rob[k].final_y);
				}
			}
			robo1.g++;
			robo1.f = robo1.g + robo1.h;
			int k{};
			while (k<q -> size()){
				if (compare_structs(robo1, q -> at(k), r, t)){
					break;
				}
				k++;
			}
			if (k >= q -> size()){
				k = 0;
				if (q -> size() > 0){
    				while (k < q -> size()){
    				    if(q -> at(k).f > robo1.f){
    					k++;
    				    }else{
    				        break;
    				    }
    				}
    				q -> insert(q -> begin() + k,robo1);
				}else{
				    q -> insert(q -> begin(),robo1);
				}
			}else{
				if (q -> at(k).g > robo1.g){
					q -> at(k) = robo1;
				}
			}
		}
		}
		
		if(robo.rob[y].y + 1 < m && robo.mat[robo.rob[y].x][robo.rob[y].y + 1] != -2 && robo.mat[robo.rob[y].x][robo.rob[y].y + 1] != -3){
		robo1 = right(robo, y, m);
robo1.h = 0;
		for (int k{};k<r;k++){
				if (robo1.h < abs(robo1.rob[k].x - robo1.rob[k].final_x) + abs(robo1.rob[k].y - robo1.rob[k].final_y)){
					robo1.h = abs(robo1.rob[k].x - robo1.rob[k].final_x) + abs(robo1.rob[k].y - robo1.rob[k].final_y);
				}
			}
			robo1.g++;
			robo1.f = robo1.g + robo1.h;
			int k{};
			while (k<q -> size()){
				if (compare_structs(robo1, q -> at(k), r, t)){
					break;
				}
				k++;
			}
			if (k >= q -> size()){
				k = 0;
				if (q -> size() > 0){
    				while (k < q -> size()){
    				    if(q -> at(k).f > robo1.f){
    					k++;
    				    }else{
    				        break;
    				    }
    				}
    				q -> insert(q -> begin() + k,robo1);
				}else{
				    q -> insert(q -> begin(),robo1);
				}
			}else{
				if (q -> at(k).g > robo1.g){
					q -> at(k) = robo1;
				}
			}
		if (robo.mat[robo.rob[y].x][robo.rob[y].y] == -4 && !robo.rob[y].item){
		for (int i{};i<t;i++){
			if (robo.task[i].x == robo.rob[y].x && robo.task[i].y == robo.rob[y].y && !robo.task[i].picked ){
			robo1 = pickup(robo, y, i);
			robo1 = right(robo1, y, m);
robo1.h = 0;
			for (int k{};k<r;k++){
				if (robo1.h < abs(robo1.rob[k].x - robo1.rob[k].final_x) + abs(robo1.rob[k].y - robo1.rob[k].final_y)){
					robo1.h = abs(robo1.rob[k].x - robo1.rob[k].final_x) + abs(robo1.rob[k].y - robo1.rob[k].final_y);
				}
			}
			robo1.g++;
			robo1.f = robo1.g + robo1.h;
			int k{};
			while (k<q -> size()){
				if (compare_structs(robo1, q -> at(k), r, t)){
					break;
				}
				k++;
			}
			if (k >= q -> size()){
				k = 0;
				if (q -> size() > 0){
    				while (k < q -> size()){
    				    if(q -> at(k).f > robo1.f){
    					k++;
    				    }else{
    				        break;
    				    }
    				}
    				q -> insert(q -> begin() + k,robo1);
				}else{
				    q -> insert(q -> begin(),robo1);
				}
			}else{
				if (q -> at(k).g > robo1.g){
					q -> at(k) = robo1;
				}
			}
		}
		}
		}
		if (robo.mat[robo.rob[y].x][robo.rob[y].y] == -4 && robo.rob[y].item){
		robo1 = drop(robo, y);
		robo1 = right(robo1, y, m);
robo1.h = 0;
		for (int k{};k<r;k++){
				if (robo1.h < abs(robo1.rob[k].x - robo1.rob[k].final_x) + abs(robo1.rob[k].y - robo1.rob[k].final_y)){
					robo1.h = abs(robo1.rob[k].x - robo1.rob[k].final_x) + abs(robo1.rob[k].y - robo1.rob[k].final_y);
				}
			}
			robo1.g++;
			robo1.f = robo1.g + robo1.h;
			int k{};
			while (k<q -> size()){
				if (compare_structs(robo1, q -> at(k), r, t)){
					break;
				}
				k++;
			}
			if (k >= q -> size()){
				k = 0;
				if (q -> size() > 0){
    				while (k < q -> size()){
    				    if(q -> at(k).f > robo1.f){
    					k++;
    				    }else{
    				        break;
    				    }
    				}
    				q -> insert(q -> begin() + k,robo1);
				}else{
				    q -> insert(q -> begin(),robo1);
				}
			}else{
				if (q -> at(k).g > robo1.g){
					q -> at(k) = robo1;
				}
			}
		}
		}
		
		if(robo.rob[y].y - 1 >= 0 && robo.mat[robo.rob[y].x][robo.rob[y].y - 1] != -2 && robo.mat[robo.rob[y].x][robo.rob[y].y - 1] != -3){
		robo1 = left(robo, y);
robo1.h = 0;
		for (int k{};k<r;k++){
				if (robo1.h < abs(robo1.rob[k].x - robo1.rob[k].final_x) + abs(robo1.rob[k].y - robo1.rob[k].final_y)){
					robo1.h = abs(robo1.rob[k].x - robo1.rob[k].final_x) + abs(robo1.rob[k].y - robo1.rob[k].final_y);
				}
			}
			robo1.g++;
			robo1.f = robo1.g + robo1.h;
			int k{};
			while (k<q -> size()){
				if (compare_structs(robo1, q -> at(k), r, t)){
					break;
				}
				k++;
			}
			if (k >= q -> size()){
				k = 0;
				if (q -> size() > 0){
    				while (k < q -> size()){
    				    if(q -> at(k).f > robo1.f){
    					k++;
    				    }else{
    				        break;
    				    }
    				}
    				q -> insert(q -> begin() + k,robo1);
				}else{
				    q -> insert(q -> begin(),robo1);
				}
			}else{
				if (q -> at(k).g > robo1.g){
					q -> at(k) = robo1;
				}
			}
		if (robo.mat[robo.rob[y].x][robo.rob[y].y] == -4 && !robo.rob[y].item){
		for (int i{};i<t;i++){
			if (robo.task[i].x == robo.rob[y].x && robo.task[i].y == robo.rob[y].y && !robo.task[i].picked ){
			robo1 = pickup(robo, y, i);
			robo1 = left(robo1, y);
robo1.h = 0;
			for (int k{};k<r;k++){
				if (robo1.h < abs(robo1.rob[k].x - robo1.rob[k].final_x) + abs(robo1.rob[k].y - robo1.rob[k].final_y)){
					robo1.h = abs(robo1.rob[k].x - robo1.rob[k].final_x) + abs(robo1.rob[k].y - robo1.rob[k].final_y);
				}
			}
			robo1.g++;
			robo1.f = robo1.g + robo1.h;
			int k{};
			while (k<q -> size()){
				if (compare_structs(robo1, q -> at(k), r, t)){
					break;
				}
				k++;
			}
			if (k >= q -> size()){
				k = 0;
				if (q -> size() > 0){
    				while (k < q -> size()){
    				    if(q -> at(k).f > robo1.f){
    					k++;
    				    }else{
    				        break;
    				    }
    				}
    				q -> insert(q -> begin() + k,robo1);
				}else{
				    q -> insert(q -> begin(),robo1);
				}
			}else{
				if (q -> at(k).g > robo1.g){
					q -> at(k) = robo1;
				}
			}
		}
		}
		}
		if (robo.mat[robo.rob[y].x][robo.rob[y].y] == -4 && robo.rob[y].item){
		robo1 = drop(robo, y);
		robo1 = left(robo1, y);
robo1.h = 0;
		for (int k{};k<r;k++){
				if (robo1.h < abs(robo1.rob[k].x - robo1.rob[k].final_x) + abs(robo1.rob[k].y - robo1.rob[k].final_y)){
					robo1.h = abs(robo1.rob[k].x - robo1.rob[k].final_x) + abs(robo1.rob[k].y - robo1.rob[k].final_y);
				}
			}
			robo1.g++;
			robo1.f = robo1.g + robo1.h;
			int k{};
			while (k<q -> size()){
				if (compare_structs(robo1, q -> at(k), r, t)){
					break;
				}
				k++;
			}
			if (k >= q -> size()){
				k = 0;
				if (q -> size() > 0){
    				while (k < q -> size()){
    				    if(q -> at(k).f > robo1.f){
    					k++;
    				    }else{
    				        break;
    				    }
    				}
    				q -> insert(q -> begin() + k,robo1);
				}else{
				    q -> insert(q -> begin(),robo1);
				}
			}else{
				if (q -> at(k).g > robo1.g){
					q -> at(k) = robo1;
				}
			}
		}
		}
		
		robo1 = stay(robo);
robo1.h = 0;
		for (int k{};k<r;k++){
				if (robo1.h < abs(robo1.rob[k].x - robo1.rob[k].final_x) + abs(robo1.rob[k].y - robo1.rob[k].final_y)){
					robo1.h = abs(robo1.rob[k].x - robo1.rob[k].final_x) + abs(robo1.rob[k].y - robo1.rob[k].final_y);
				}
			}
			robo1.g++;
			robo1.f = robo1.g + robo1.h;
			int k{};
			while (k<q -> size()){
				if (compare_structs(robo1, q -> at(k), r, t)){
					break;
				}
				k++;
			}
			if (k >= q -> size()){
				k = 0;
				if (q -> size() > 0){
    				while (k < q -> size()){
    				    if(q -> at(k).f > robo1.f){
    					k++;
    				    }else{
    				        break;
    				    }
    				}
    				q -> insert(q -> begin() + k,robo1);
				}else{
				    q -> insert(q -> begin(),robo1);
				}
			}else{
				if (q -> at(k).g > robo1.g){
					q -> at(k) = robo1;
				}
			}
		if (robo.mat[robo.rob[y].x][robo.rob[y].y] == -4 && robo.rob[y].item){
		robo1 = stay(robo);
		robo1 = drop(robo1, y);
robo1.h = 0;
		for (int k{};k<r;k++){
				if (robo1.h < abs(robo1.rob[k].x - robo1.rob[k].final_x) + abs(robo1.rob[k].y - robo1.rob[k].final_y)){
					robo1.h = abs(robo1.rob[k].x - robo1.rob[k].final_x) + abs(robo1.rob[k].y - robo1.rob[k].final_y);
				}
			}
			robo1.g++;
			robo1.f = robo1.g + robo1.h;
			int k{};
			while (k<q -> size()){
				if (compare_structs(robo1, q -> at(k), r, t)){
					break;
				}
				k++;
			}
			if (k >= q -> size()){
				k = 0;
				if (q -> size() > 0){
    				while (k < q -> size()){
    				    if(q -> at(k).f > robo1.f){
    					k++;
    				    }else{
    				        break;
    				    }
    				}
    				q -> insert(q -> begin() + k,robo1);
				}else{
				    q -> insert(q -> begin(),robo1);
				}
			}else{
				if (q -> at(k).g > robo1.g){
					q -> at(k) = robo1;
				}
			}
		}
	}else{
		robots robo1;
		if(robo.rob[y].x + 1 < n && robo.mat[robo.rob[y].x + 1][robo.rob[y].y] != -2 && robo.mat[robo.rob[y].x + 1][robo.rob[y].y] != -3){
			robo1 = down(robo, y, n);
			combinations(robo1, y-1, n, m, q, t, r);
			if (robo.mat[robo.rob[y].x][robo.rob[y].y] == -4 && !robo.rob[y].item){				
				for (int i{};i<t;i++){
					if (robo.task[i].x == robo.rob[y].x && robo.task[i].y == robo.rob[y].y && !robo.task[i].picked ){
						robo1 = pickup(robo, y, i);
						robo1 = down(robo1, y, n);
						combinations(robo1, y-1, n, m, q, t, r);
					}
				}
			}
			if (robo.mat[robo.rob[y].x][robo.rob[y].y] == -4 && robo.rob[y].item){
				robo1 = drop(robo, y);
				robo1 = down(robo1, y, n);
				combinations(robo1, y-1, n, m, q, t, r);
			}
		}
		
		if(robo.rob[y].x - 1 >= 0 && robo.mat[robo.rob[y].x - 1][robo.rob[y].y] != -2 && robo.mat[robo.rob[y].x - 1][robo.rob[y].y] != -3){
		robo1 = up(robo, y);
		combinations(robo1, y-1, n, m, q, t, r);
		if (robo.mat[robo.rob[y].x][robo.rob[y].y] == -4 && !robo.rob[y].item){
		for (int i{};i<t;i++){
			if (robo.task[i].x == robo.rob[y].x && robo.task[i].y == robo.rob[y].y && !robo.task[i].picked ){
			robo1 = pickup(robo, y, i);
			robo1 = up(robo1, y);
			combinations(robo1, y-1, n, m, q, t, r);
		}
		}
		}
		if (robo.mat[robo.rob[y].x][robo.rob[y].y] == -4 && robo.rob[y].item){
		robo1 = drop(robo, y);
		robo1 = up(robo1, y);
		combinations(robo1, y-1, n, m, q, t, r);
		}
		}
	
		if(robo.rob[y].y + 1 < m && robo.mat[robo.rob[y].x][robo.rob[y].y + 1] != -2 && robo.mat[robo.rob[y].x][robo.rob[y].y + 1] != -3){
		robo1 = right(robo, y, m);
		combinations(robo1, y-1, n, m, q, t, r);
		if (robo.mat[robo.rob[y].x][robo.rob[y].y] == -4 && !robo.rob[y].item){
		for (int i{};i<t;i++){
			if (robo.task[i].x == robo.rob[y].x && robo.task[i].y == robo.rob[y].y && !robo.task[i].picked ){
			robo1 = pickup(robo, y, i);
			robo1 = right(robo1, y, m);
			combinations(robo1, y-1, n, m, q, t, r);
		}
		}
		}
		if (robo.mat[robo.rob[y].x][robo.rob[y].y] == -4 && robo.rob[y].item){
		robo1 = drop(robo, y);
		robo1 = right(robo1, y, m);
		combinations(robo1, y-1, n, m, q, t, r);
		}
		}
		
		if(robo.rob[y].y - 1 >= 0 && robo.mat[robo.rob[y].x][robo.rob[y].y - 1] != -2 && robo.mat[robo.rob[y].x][robo.rob[y].y - 1] != -3){
		robo1 = left(robo, y);
		combinations(robo1, y-1, n, m, q, t, r);
		if (robo.mat[robo.rob[y].x][robo.rob[y].y] == -4 && !robo.rob[y].item){
		for (int i{};i<t;i++){
			if (robo.task[i].x == robo.rob[y].x && robo.task[i].y == robo.rob[y].y && !robo.task[i].picked ){
			robo1 = pickup(robo, y, i);
			robo1 = left(robo1, y);
			combinations(robo1, y-1, n, m, q, t, r);
		}
		}
		}
		if (robo.mat[robo.rob[y].x][robo.rob[y].y] == -4 && robo.rob[y].item){
		robo1 = drop(robo, y);
		robo1 = left(robo1, y);
		combinations(robo1, y-1, n, m, q, t, r);
		}
		}
		
		
		robo1 = stay(robo);
		combinations(robo1, y-1, n, m, q, t, r);
		
		if (robo.mat[robo.rob[y].x][robo.rob[y].y] == -4 && robo.rob[y].item){
			robo1 = stay(robo);
			robo1 = drop(robo1, y);
			combinations(robo1, y-1, n, m, q, t, r);
		}
	}
}
bool goal(robots robo, int r, int t){
	for (int i{};i<r;i++){
		if (robo.rob[i].x == robo.rob[i].final_x && robo.rob[i].y == robo.rob[i].final_y){
			continue;
		}else{
			return false;
		}
	}
	for (int j{};j<t;j++){
		if (robo.task[j].x == robo.task[j].dest_x && robo.task[j].y == robo.task[j].dest_y){
			continue;
		}else{
			return false;
		}
	}
	return true;
}
int main(){
	int n{},m{},r{},t{},te{},ob{};
	cout<<"Enter size of grid:"<<endl;
	cin>>n>>m;
	int grid[n][m]{};
	cout<<"Enter no. of robots:"<<endl;
	cin>>r;
	robots robo, robo_goal;
	for (int i{};i<r;i++){
		cout<<"Enter parameters for robot "<<i+1<<":"<<endl;
		cin>>robo.rob[i].x;
		cin>>robo.rob[i].y;
		grid[robo.rob[i].x][robo.rob[i].y] = -1;
		cin>>robo.rob[i].final_x;
		cin>>robo.rob[i].final_y;
		grid[robo.rob[i].final_x][robo.rob[i].final_y] = -1;
		if (robo.h < abs(robo.rob[i].final_x - robo.rob[i].x) + abs(robo.rob[i].final_y - robo.rob[i].y)){
			robo.h = abs(robo.rob[i].final_x - robo.rob[i].x) + abs(robo.rob[i].final_y - robo.rob[i].y);
		}
		robo.f = robo.h;
	}
	cout<<"Enter no. of tasks:"<<endl;
	cin>>t;
	for (int i{};i<t;i++){
		cout<<"Enter parameters for task "<<i+1<<":"<<endl;
		cin>>robo.task[i].x;
		cin>>robo.task[i].y;
		grid[robo.task[i].x][robo.task[i].y] = -4;
		cin>>robo.task[i].dest_x;
		cin>>robo.task[i].dest_y;
		grid[robo.task[i].dest_x][robo.task[i].dest_y] = -4;
	}
	cout<<"enter no. of temporary locations:"<<endl;
	cin>>te;
	for (int i{};i<te;i++){
		int temp1{};
		int temp2{};
		cout<<"enter temporary location "<<i+1<<endl;
		cin>>temp1;
		cin>>temp2;
		grid[temp1][temp2] = -4;
	}
	cout<<"enter no. of obstacles:"<<endl;
	cin>>ob;
	for (int i{};i<ob;i++){
		int temp1{};
		int temp2{};
		cout<<"enter obstacle location "<<i+1<<endl;
		cin>>temp1;
		cin>>temp2;
		grid[temp1][temp2] = -2;
	}
	for (int i{};i<n;i++){
		for (int j{};j<m;j++){
			robo.mat[i][j] = grid[i][j];
		}
	}
	// initialize queue
	// queue of pointers of type robots
	
	vector <robots> q;
	q.push_back(robo);
	int res{}, time_s{};
	time_t start, end;
	time(&start);
	while (!q.empty()){
		// queue and all logic
		robots robo{q.at(q.size() - 1)};
		if (robo.time_step != time_s){
		    time_s = robo.time_step;
		    cout<<endl<<"================================"<<endl<<time_s<<endl<<"================================"<<endl;
		}
		cout<<"....................."<<endl;
		q.pop_back();
		if (goal(robo, r, t)){
			robo_goal = robo;
			cout<<"GOAL FOUND"<<endl;
			cout<<"TIME STEPS: "<<robo_goal.time_step<<endl;
			break;
		}
		combinations(robo, r-1, n, m, &q, t, r);
		res++;
	}
	time(&end);
	double time_taken = double(end - start);
    	cout << "Time taken by program is : " << fixed << time_taken << setprecision(2);
    	cout << " sec " << endl;
	cout<<"No. of configurations explored: "<<res<<endl;
	return 0;
}
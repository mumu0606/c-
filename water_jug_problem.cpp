//幅優先探索でWater Jug Problemを解く
#include <iostream>
#include <string>
#include <vector>
#include <unistd.h>

using namespace std;

class Status
{
  public:
    string transition;
    int pitcher[3];
    Status(int p1, int p2, int p3){
      transition = "";
      pitcher[0] = p1;
      pitcher[1] = p2;
      pitcher[2] = p3;
    }
};

const int PitcherNum = 3;
const int PitcherMax[PitcherNum] = {8, 5 ,3};
int Pitcher[PitcherNum];
vector<Status> queue; //状態を保持するのではなくて変遷を保持すれば良い
vector<vector<int> > visitedList;
void setPitcher(){
  Pitcher[0] = 8;
  Pitcher[1] = 0;
  Pitcher[2] = 0;
}

//ある番号からある番号へ移せるかどうか
bool canTransfer(int from_n, int to_n){
  if(Pitcher[from_n] == 0){return false;}
  if(Pitcher[to_n] == PitcherMax[to_n]){return false;}
  return true;
}

//指定した番号のピッチャーからピッチャーへ液体を移し替える
void transferLiquid(int from_n, int to_n){
  //移し替える液体の量
  while(true){
    if(!(canTransfer(from_n, to_n))){break;}
    Pitcher[from_n] -= 1;
    Pitcher[to_n] += 1;
  }
}

//未展開リストをqueueに突っ込む
void setQueue(){
  Status status = Status(Pitcher[0], Pitcher[1], Pitcher[2]);
  status.transition = queue[0].transition + (" " + to_string(Pitcher[0]) + " " + to_string(Pitcher[1]) + " " + to_string(Pitcher[2]) + "\n");
  queue.push_back(status);
  cout << "transition" << status.transition << endl;
}

//訪問済みかどうかの判定を行う。もし新規ならvisitedListに追加する
bool checkVisited(){
  for(auto itr = visitedList.begin();itr != visitedList.end();itr++){
    vector<int> arr = *itr;
    if(arr[0] != Pitcher[0]){return false;}
    if(arr[1] != Pitcher[1]){return false;}
    if(arr[2] != Pitcher[2]){return false;}
    if((arr[0] != Pitcher[0]) or (arr[1] != Pitcher[1]) or (arr[2] != Pitcher[2])){
      vector<int> node;
      node.push_back(Pitcher[0]);
      node.push_back(Pitcher[1]);
      node.push_back(Pitcher[2]);
      visitedList.push_back(node);
      return true;
    }
  }
  return false;
}

//終了判定を行う
bool checkFinish(){
  int count = 0;
  for(int i = 0;i < PitcherNum;i++){
    if(Pitcher[i] == 4){count += 1;}
  }

  if(count == 2){
    return true;
  }else{
    return false;
  }
}

//queueに格納する状態を配列でなく構造体に。一度訪れたqueueを排除

int main(){
  int transfer_count = 0;
  bool flag = true;
  //訪問済みリストを作成
  setPitcher();
  Status status = Status(Pitcher[0], Pitcher[1], Pitcher[2]);
  status.transition = "8 0 0\n";
  queue.push_back(status);
  while(queue.size() != 0){
    Pitcher[0] = queue[0].pitcher[0];
    Pitcher[1] = queue[0].pitcher[1];
    Pitcher[2] = queue[0].pitcher[2];
    //sleep(1);
    // << "queue" << endl;
    if(checkVisited()){break;}
    cout << Pitcher[0] << " " << Pitcher[1] << " " << Pitcher[2] << endl;
    if(checkFinish()){break;}
    //

    for(int i = 0;i < PitcherNum;i++){
      for(int j = 0;j < PitcherNum;j++){
        if(i == j){continue;}
        if(canTransfer(i, j)){
          int temp1 = Pitcher[i];
          int temp2 = Pitcher[j];
          transferLiquid(i, j);

          setQueue();
          Pitcher[i] = temp1;
          Pitcher[j] = temp2;
        }
      }
    }
    queue.erase(queue.begin());
  }
  cout << "transition" << endl;
  cout << queue[0].transition;
  return 0;
}
int xs = 400;
int ys = 400;

int order = 50;

ArrayList<int[]> known = new ArrayList<int[]>();

void setup(){
  size(400, 400);
}

void draw(){
  float bestDist = xs*xs + ys*ys + 1;
  int bestx = 0;
  int besty = 0;
  
  for(int i=0; i<order; i++){
    int x = floor(random(0, xs));
    int y = floor(random(0, ys));
    float min = xs*xs + ys*ys;
    
    for(int j=0; j<known.size(); j++){
      float dist = pow(x-known.get(j)[0], 2) + pow(y-known.get(j)[1], 2);
      min = min(min, dist);
    }
    
    if(min < bestDist){
      bestx = x;
      besty = y;
      bestDist = min;
    }
  }
    
  point(bestx, besty);
  int[] pt = {bestx, besty};
  known.add(pt);
}

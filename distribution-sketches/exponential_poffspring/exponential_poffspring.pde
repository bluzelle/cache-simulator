int xs = 400;
int ys = 400;

int nodes = 0;
int maxNodes = 10000;

float breakChance = 0.07;
float cityRadius= 7;
int min_sites = 20;

ArrayList<float[]> known = new ArrayList<float[]>();

void setup(){
  size(600, 600);
}

void draw(){
  float x;
  float y;
  if (known.size() < min_sites || random(0, 1) < breakChance){
    x = random(0, xs);
    y = random(0, ys);
  }else{
    float angle = random(0, 2*PI);
    float distance = -log(random(0, 1))*cityRadius;
    float[] base = known.get(floor(random(0, known.size())));
    
    x = base[0] + sin(angle)*distance;
    y = base[1] + cos(angle)*distance;
  }
  
  point(floor(x)+100, floor(y)+100);
  float[] pt = {x, y};
  known.add(pt);
  nodes++;
  if(nodes%100 == 0){
    println(nodes); 
  }
  if(nodes >= maxNodes){
    noLoop();
    println("done");
  }
}

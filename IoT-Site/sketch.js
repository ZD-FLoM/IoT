// Main file for running IoT Showcase by Zachary Daulton @ZacharyDaulton

// module aliases
var Engine = Matter.Engine,
  // Render = Matter.Render,
  World = Matter.World,
  Bodies = Matter.Bodies,
  Body = Matter.Body;
  Constraint = Matter.Constraint;
  Engine.velocityIterations = 4;
  Engine.positionIterations = 6;


var incomingString = ("loading"+" "+ "1"); 
var prevString = ("Loadings" + " " + "0");
var subbed = undefined;
var data = 120;
var predata = 0;
var feedbackpos = 0;
var angler = 0;

var engine;
var world;
var circles = [];
var boundaries = [];



var ground;
var up = 800;
var trigger1 = 0;
var trigger2 = 0;

var anglesum = 0;
var time = 0;
var easing = 0.05;


var container = 0x0001,
        paddles = 0x0002,
        invisible = 0x0004,
        ball = 0x0008;


function setup() {
  createCanvas(600, 800);
  engine = Engine.create();
  world = engine.world;


engine.world.gravity.y = 1;
engine.world.gravity.x = 0;

for (var i = 5; i < 20; i++) {
circles.push(new Circle(40, i*10, 8, 1, ball, container | paddles));
circles.push(new Circle(540, i*10, 8, 1, ball, container | paddles));
}



  boundaries.push(new Boundary(100, 700, 350, 50, .7, false, 0, paddles, ball, true)); // left paddle
  boundaries.push(new Boundary(10, 400, 800, 40, 1.5708, true, -1, container, ball, true)); // left wall
  boundaries.push(new Boundary(300, 790, 700, 20, 0, true, -1, container, ball, true)); // ground wall
  boundaries.push(new Boundary(300, 820, 700, 20, 0, true, -2, invisible, paddles, true)); // lowerGround
  boundaries.push(new Boundary(590, 400, 800, 40, 1.5708, true, -1, container, ball, true)); // right wall
  boundaries.push(new Boundary(500, 700, 350, 50, 2.4, false, -1, paddles, ball, true)); // right paddle
  boundaries.push(new Boundary(152, 780, 300, 30, -.1, true, -1, paddles, ball, true)); // compoundramp
  boundaries.push(new Boundary(448, 780, 300, 30, .1, true, -1, paddles, ball, true)); // compoundramp
  boundaries.push(new Boundary(300, 0, 600, 30, 0, true, -1, paddles, ball, true)); // ceiling

    // Cups
    boundaries.push(new Boundary(255, 200, 100, 20, 1.5708, true, -1, paddles, ball, false)); // ceiling
    boundaries.push(new Boundary(300, 250, 110, 20, 0, true, -1, paddles, ball, false)); // ceiling
    boundaries.push(new Boundary(345, 200, 100, 20, 1.5708, true, -1, paddles, ball, false)); // ceiling

    boundaries.push(new Boundary(110, 465, 80, 20, 1.5708, true, -1, paddles, ball, false)); // ceiling
    boundaries.push(new Boundary(150, 500, 100, 20, 0, true, -1, paddles, ball, false)); // ceiling
    boundaries.push(new Boundary(190, 465, 80, 20, 1.5708, true, -1, paddles, ball, false)); // ceiling

    boundaries.push(new Boundary(410, 465, 80, 20, 1.5708, true, -1, paddles, ball, false)); // ceiling
    boundaries.push(new Boundary(450, 500, 100, 20, 0, true, -1, paddles, ball, false)); // ceiling
    boundaries.push(new Boundary(490, 465, 80, 20, 1.5708, true, -1, paddles, ball, false)); // ceiling

Cup1 = Body.create({parts: [boundaries[9].body, boundaries[10].body, boundaries[11].body],
   isStatic: true,
   collisionFilter:{group: -1, category: paddles, mask: ball},
});

Cup2 = Body.create({parts: [boundaries[12].body, boundaries[13].body, boundaries[14].body],
   isStatic: true,
   collisionFilter:{group: -1, category: paddles, mask: ball},
});

Cup3 = Body.create({parts: [boundaries[15].body, boundaries[16].body, boundaries[17].body],
   isStatic: true,
   collisionFilter:{group: -1, category: paddles, mask: ball},
});


var constraint1 = Constraint.create({
    bodyA: boundaries[1].body,
    pointA: { x : -190, y: 350},
    bodyB: boundaries[0].body,
    pointB: { x : -50, y: 0},
    length:1,
   stiffness: .01,
});

World.add(world, [constraint1, Cup1, Cup2, Cup3]);


var constraint2 = Constraint.create({     // Right paddle[5] and Wall [4]
    bodyA: boundaries[4].body,
    pointA: { x : 190, y: 350},
    bodyB: boundaries[5].body,
    pointB: { x : 50, y: 0},
    length:1,
   stiffness: .01,
});

World.add(world, constraint2);

var constraint3 = Constraint.create({     // left paddle and ground
    bodyA: boundaries[0].body,
    pointA: { x : 300, y: 0},
    bodyB: boundaries[3].body,
    pointB: { x : 190, y: -180},
    length:1,
   stiffness: .01,
});

World.add(world, constraint3);

var constraint4 = Constraint.create({     // right paddle and ground
    bodyA: boundaries[5].body,
    pointA: { x : -300, y: 0},
    bodyB: boundaries[3].body,
    pointB: { x : -190, y: -180},
    length:1,
   stiffness: .01,
});

World.add(world, constraint4);




}


function mousePressed() {
  circles.push(new Circle(mouseX, mouseY, 8, 1, ball, container | paddles));
}

function draw() {
  background(51);
 Engine.update(engine);

subbed = (splitTokens(incomingString, " "))[0];
data = parseFloat((splitTokens(incomingString, " "))[1]);
predata = parseFloat((splitTokens(prevString, " "))[1]);
 

if (subbed == "/servo" && incomingString != prevString) {

feedbackpos = map(data, 120,660,0,3.14159);

var angleto = [];
print(data," ", predata);
if (data > (predata+2) || data < (predata-2)){

          if (anglesum < feedbackpos && (data-predata) > 0){
                 Body.rotate(Cup1, .1, { x: 300, y: 200 } );
                 Body.rotate(Cup2, .1, { x: 150, y: 500 } );
                 Body.rotate(Cup3, .1, { x: 450, y: 500 } );
                  angleto.push(.1);

          for (i = 0; i < angleto.length; i++){
              anglesum +=angleto[i];
                          }
               }

               if (anglesum > feedbackpos && (data-predata) < 0){
                 Body.rotate(Cup1, -.1, { x: 300, y: 200 } );
                 Body.rotate(Cup2, -.1, { x: 150, y: 500 } );
                 Body.rotate(Cup3, -.1, { x: 450, y: 500 } );
                  angleto.push(-.1);

          for (i = 0; i < angleto.length; i++){
              anglesum +=angleto[i];
                          }
               }

        }

  prevString = incomingString;
}
//print(feedbackpos);


if (incomingString == "/p1 1" && trigger1 == 0) {
Body.applyForce(boundaries[0].body, { x: 0, y: 760 }, { x: 1, y: -1}); // left key left paddle
trigger1 = 1;
}

if (incomingString == "/p1 0" && trigger1 == 1) {
trigger1 = 0;
}

if (incomingString == "/p2 1" && trigger2 == 0) {
Body.applyForce(boundaries[5].body, { x: 600, y: 800 }, { x: -1, y: -1}); // left key left paddle
trigger2 = 1;
}

if (incomingString == "/p2 0" && trigger2 == 1) {
trigger2 = 0;
}



  for (var i = 0; i < boundaries.length; i++) {
    boundaries[i].show();
  }

  for (var i = 0; i < circles.length; i++) {
    circles[i].show();
  }

// print(Cup1.angle);




 
}


  function keyPressed() {
  if (keyCode === 37) {
   Body.applyForce(boundaries[0].body, { x: 0, y: 760 }, { x: 1, y: -1}); // left key left paddle
  }

   if (keyCode === 39) {
   Body.applyForce(boundaries[5].body, { x: 600, y: 800 }, { x: -1, y: -1 });
 }




}




// Code for rendering MatterJS objects in P5JS by Daniel Shiffman
// http://codingtra.in
// Original Code: https://youtu.be/uITcoKpbQq4
// Changes made for IoT Showcase by Zachary Daulton @ZacharyDaulton

function Boundary(x, y, w, h, a, s, g, c, m, r) {

this.ren = r;

  var options = {
    friction: 0,
    restitution: .1,
    angle: a,
    isStatic: s,
    collisionFilter:{group: g, category: c, mask: m},
  }




  this.body = Bodies.rectangle(x, y, w, h, options);
  this.w = w;
  this.h = h;

  if (this.ren == true){
  World.add(world, this.body);
  console.log(this.body);
  }

  this.show = function() {
    var pos = this.body.position;
    var angle = this.body.angle;
    push();
    translate(pos.x, pos.y);
    rotate(angle);
    rectMode(CENTER);
    strokeWeight(1);
    noStroke();
    fill(0);
    rect(0, 0, this.w, this.h);
    pop();
  }



}
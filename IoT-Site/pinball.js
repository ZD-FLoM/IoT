// Code for rendering MatterJS objects in P5JS by Daniel Shiffman
// http://codingtra.in
// Original Code: https://youtu.be/uITcoKpbQq4
// Changes made for IoT Showcase by Zachary Daulton @ZacharyDaulton

function Circle(x, y, r, g, c, m) {
  var options = {
    friction: 0,
    frictionStatic: 0,
    restitution: 0.8,
    collisionFilter:{group: g, category: c, mask: m},

  }
  this.body = Bodies.circle(x, y, r, options);
  this.r = r;
  World.add(world, this.body);

  this.show = function() {
    var pos = this.body.position;
    var angle = this.body.angle;
    push();
    translate(pos.x, pos.y);
    rotate(angle);
    rectMode(CENTER);
    strokeWeight(1);
    stroke(255);
    fill(127);
    ellipse(0, 0, this.r * 2);
    pop();
  }

}
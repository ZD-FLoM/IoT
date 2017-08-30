// Original Code rendering MatterJS objects in P5JS by Daniel Shiffman: https://youtu.be/uITcoKpbQq4

// All changes made for IoT Showcase by Zachary Daulton @ZacharyDaulton
// All comments made by Zachary Daulton

function Circle(x, y, r, g, c, m) {
  var options = {
    friction: 0,
    frictionStatic: 0,
    restitution: 0.8,
    collisionFilter:{group: g, category: c, mask: m},    // Collision assignments hierarchy category and mask not needed at this time

  }
  this.body = Bodies.circle(x, y, r, options);          // r for radius, as opposed to r for render in boundary object
  this.r = r;
  World.add(world, this.body);

  this.show = function() {                            // Renders the object through P5js instead of MatterJS
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

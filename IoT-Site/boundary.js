// Original Code rendering MatterJS objects in P5JS by Daniel Shiffman: https://youtu.be/uITcoKpbQq4

// All changes made for IoT Showcase by Zachary Daulton @ZacharyDaulton
// All comments made by Zachary Daulton

function Boundary(x, y, w, h, a, s, g, c, m, r) {

this.ren = r;                                              // variable for choosing to render the object in MatterJS. 
                                                           // Compound object parts should not render, only the end result compound

  var options = {
    friction: 0,
    restitution: .1,                                        // Object elasticity
    angle: a,
    isStatic: s,
    collisionFilter:{group: g, category: c, mask: m},         // Collision assignments hierarchy
  }




  this.body = Bodies.rectangle(x, y, w, h, options);
  this.w = w;
  this.h = h;

  if (this.ren == true){                                     // Add to the MatterJS world if render is true
  World.add(world, this.body);
  console.log(this.body);
  }

  this.show = function() {                                  // Renders the object through P5js instead of MatterJS
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

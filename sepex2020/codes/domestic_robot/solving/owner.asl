!drink(beer). // initial goal

+!drink(beer): has(owner,beer)
   <- .print("I have beer. So, I am drinking");
      sip(beer);
	  .wait(1000); //wait a second and keep drinking
	  !drink(beer).

+!drink(beer): not has(owner,beer)
   <- .print("I do not have any beer. Asking the robot");
      .send(robot,achieve,has(owner,beer));
	  .wait(has(owner,beer));
	  !drink(beer).

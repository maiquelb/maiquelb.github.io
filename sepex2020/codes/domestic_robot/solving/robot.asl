/* Initial beliefs */

// initially, I believe that there are some beers in the fridge
available(beer,fridge).

// my owner should not consume more than 10 beers a day :-)
limit(beer,10).


+!has(owner,beer):available(beer,fridge) 
   <- .print("The owner wants beer");
      !go_to(fridge);
	  open(fridge);
	  get(beer);
	  close(fridge);
	  !go_to(owner);
	  hand_in(beer).
	  
	  
+!has(owner,beer):not available(beer,fridge)
   <- .print("Waiting for some available beer.");
      .wait(available(beer,fridge));
	  !has(owner,beer).

	  
	  	  
+!go_to(Place): not at(robot,Place)
   <- move_towards(Place);
      !go_to(Place).
	  
+!go_to(Place): at(robot,Place).

+stock(beer,0) : available(beer,fridge)
   <- -available(beer,fridge).
   
+stock(beer,N) : N>0 & not available(beer,fridge)
   <- +available(beer,fridge).

-available(beer,fridge)
   <- .print("There is not beer. Asking to supermarket.");
      .send(supermarket, achieve, order(beer,5)).
	  
+delievered(beer,N,OrderId)
   <- +available(beer,fridge).

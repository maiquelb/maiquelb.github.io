last_order_id(1). //initial belief: the number of the laste delivered order

+!order(beer, N)[source(Ag)]
   <- .print(Ag, "wants to order ", N, " beer");
      deliver(beer,N);
	  ?last_order_id(OId);
	  -+last_order_id(OId+1);
	  .send(robot,tell,delievered(beer,N,OId+1)).
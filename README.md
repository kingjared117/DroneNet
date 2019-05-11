# DroneNet

The goal of this project is to simulate a drone cloud.  A net of nodes are created and they have to let everyone in the net know data about themselves.  They do this by broadcasting the data to the nearby nodes.  It is needed to let every node get a chance to speak and for each node to be listening to only one node at a time.  This means that if a node is speaking all the nearby nodes must be listening instead of transmiting.
Below is the structure for the solution that was devolped.

General Structure
We plan to have several different data structures that all nodes will have access to,  One is a list of all nodes.  Each node struct will know its position and how many times the node has broadcasted.  It will also contain the lock for the node and the condition variable.  One lock is for the node transmiting.  The condition variable states what frequency the node is broadcasting and listening on.

Broadcasting 
To broadcast the node will first check to see if there are any other nodes that have a lower counter then them.  If any node has a lower counter, and is on the same frequency it will instead wait a random amount of time before checking again.  Otherwise it will then lock its transmitting lock and then check everyone in range on the same frequency transmitting lock,  If they are all open it will take their listening locks and then broadcast its message.  After it has broadcast its message it will then increment its counter and the free the locks.  If another node transmitting lock is taken it will then unlock itself and wait a random amount of time.  After its random wait length the node will then check again to see if it can broadcast.  Noise makers will ignore this and just broadcast for a set amount of time.  This will make it so that no nearby nodes will be able to broadcast on the same frequency.  Noise makers will not have a counter and the other nodes will not wait for them to broadcast first.

Deadlock avoidance
The first possible deadlock occurs right away when all the nodes start checking if the can transmit at the same time.  This is solved by the fact that each node is waiting a different random amount of time after checking before checking again.  Thus even though there may be an initial collision, as we continue the collision becomes less and less likely.

Fairness
Our implementation is brutally fair.  Since it waits for everyone to have a chance to broadcast before it begins to broadcast again.  This means that everyone is guaranteed a chance to talk, but this does cause a huge hit on our efficiency.  At first we will have lots of concurrency since as many nodes as possible will be talking, but near the end of the cycle less and less nodes will be talking at the same time.  This will repeat every cycle.

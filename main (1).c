#include <stdio.h>
#include <stdlib.h>

// declare global variables
int numTracks;
int seqSize;
int schedAlgo;
int *sequence = NULL;

/*******************************************/
void option1() {
	// prompt for number of concentric tracks, size of sequence, and scheduling algorithm
	printf("Enter the number of concentric tracks : ");
	scanf("%d",&numTracks);
	printf("\nEnter size of Sequence : ");
	scanf("%d",&seqSize);
	printf("\nEnter Schedualing Algorithm (0=FIFO, 1=SSTF) : ");
	scanf("%d",&schedAlgo);
	if (sequence != NULL){
		free(sequence);
	}
	// allocate memory for sequence dynamic array
	sequence = (int *)malloc(seqSize * sizeof(int));
	return;
}


/*******************************************/
void option2() {
	// declare local variables */
	int i;
	int j;
	int temp;
	int smallestIndex;
	int *sortedSeq;
	int traversedTrack = 0;
	float avgDelay = 0.0;
	int totalDelay = 0;
	int shiftRight = 0;
	int longestDelay = 0;
	int longestTrack = 0;
	int numMoves = 0;

	printf("\nEnter sequence of tracks to seek: ");
	// for-loop: prompt for each track in sequence
	for( i = 0; i < seqSize; i++){   
	   scanf("%d", &sequence[i]);
	   printf("%d", sequence[i]);
	   printf("\n ");
		// if track is out of range (<0 or > number of tracks, printe message and return
		if (sequence[i] < 0 || sequence[i] >= numTracks){
         printf("\nOut of range!");
         return;
    }
	}
	// If FIFO
	if (schedAlgo == 0){
		printf("\nTraversed sequence: ");
	  for( i = 0; i < seqSize; i++){
	     printf("%d", sequence[i]);
	     printf(" "); 
	  }
		// initilize number of traversed tracks to first track in sequence
		traversedTrack = sequence[0];
		// for loop: 
		for(i = 1; i < seqSize; i++){
			// update nummber of trversed tracks based on absolute value of difference between adjacent indices in sequence
			traversedTrack += abs(sequence[i]-sequence[i-1]); 
		}
		// print number of traversed tracks 
		printf("\nThe number of tracks traversed is: ");	
		printf("%d", traversedTrack);
	} 
	// Else SSTF
	else if(schedAlgo == 1){
		// allocate memory for sorted sequence dynamic array & initialize to original sequence
		sortedSeq = (int *) malloc(seqSize * sizeof(int));
		for(i = 0; i < seqSize; i++){
		   sortedSeq[i] = sequence[i];
		}
		 
		// sort elements in increasing order using a sorting algorithm (Selection sort, etc.)
		for (i = 0; i < seqSize; i++){
      smallestIndex = i;
			for (j = i + 1; j < seqSize; j++) {
				if (sortedSeq[j] < sortedSeq[smallestIndex]) {
					smallestIndex = j;
      	}
   		}
   		temp = sortedSeq[i];
   		sortedSeq[i] = sortedSeq[smallestIndex];
   		sortedSeq[smallestIndex] = temp;
		}
		// for-loop: 
		for( i = 0; i < seqSize; i++){  
			j = i+1;
			shiftRight = 0;
			while( (j < seqSize) && (sequence[i] != sortedSeq[j])){
			  j++;
			}    
			if(j < seqSize){
			// calculate delays based on difference between track position in sorted array and original array
				shiftRight = j-i;
			  totalDelay += shiftRight;
			  numMoves++;
			// update value of longest delay if number of moved positions is greater than current longest delay		
				if(shiftRight > longestDelay){
					longestDelay = shiftRight;
			  	longestTrack = sequence[i];
				}
			}
		}
		// initilize number of traversed tracks to first track in sequence
		// print traversed sequence
		printf("\nTraversed sequence: ");
		// for loop:
		for( i= 0; i < seqSize; i++){
		  printf("%d", sortedSeq[i]);
			printf(" ");
		}
		// calculate and print average_delay
		avgDelay = totalDelay / numMoves;
			printf("\nThe average delay of all tracks processed later is: ");
		printf("\n%.1f", avgDelay-1);
		// print number of traversed tracks
    // print longest delay
    printf("\nThe longest delay experienced by a track is: %d by track %d\n",longestDelay,longestTrack);
  }   
	return;
} 
		
/***************************************************************/
int main() {
	int choice = 0;
	do
	{
		printf("\n\nDisk Scheduling\n"
			   "1) Enter Parameters\n"
			   "2) Schedule disk tracks\n"
			   "3) Quit\n"
			   "Enter Selection:\n");
		scanf("%d", &choice);
		printf("%d", choice);
		switch (choice)
		{
		case 1:
			option1();
			break;
		case 2:
			option2();
			break;
		default:
			printf("Exiting\n");
		}
	} while (choice != 3);
	return 1;
}

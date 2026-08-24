#include<stdio.h>

int main(){

    int slot, car, bus, motor, load=0, highestLoad=0, total=0, congestion=0, light=0, moderate=0, heavy=0, severe=0;

    scanf("%d", &slot);
  if(slot>=2&&slot<=10)
  {
     for(int i=1; i<=slot; i++)
     {
            scanf("%d %d %d", &car, &bus, &motor);
             if(car>=0 && car<=100 && bus>=0 && bus<=30 && motor>=0 && motor<=100) //constraints
             {
              load = car+ 3*bus+motor;
              total += load;

              if (load>highestLoad)
              {
                    highestLoad = load;
              }

                if(load<=30)
               {
                 printf("Slot%d: LIGHT-Load %d\n", i, load);
                 congestion += 0;
                 light++;
               }
                 else if(load>30 && load<=59)
               {
                 printf("Slot%d: MODERATE-Load %d\n", i, load);
                 congestion += 2;
                 moderate++;
               }
                 else if(load>60 && load<=89)
               {
                 printf("Slot%d: HEAVY-Load %d\n", i, load);
                 congestion += 5;
                 heavy++;
               }
                 else
               {
                  printf("Slot%d: SEVERE-Load %d\n", i, load);
                  severe++;
                 congestion += 8;
               }

             }

     }

     printf("Total Load: %d\n", total);
     printf("\nHighest Load: %d", highestLoad);
     printf("\nSlot Counts: LIGHT=%d, MODERATE=%d, HEAVY=%d, SEVERE=%d", light, moderate, heavy, severe);
     printf("\nCongestion Points: %d\n", congestion);

  //The road has only 1 HEAVY slot and 1 MODERATE slot,so its status is NORMAL. Mximum congestion points is 7, so the road status is NORMAL.
  //Two time slots are MODERATE,while there are no HEAVY or SEVERE slots. Therefore, the road status is BUSY.
  //two slots are HEAVY and there is no SEVERE slot, the road status is CONGESTED.
  //The presence of even one SEVERE slot makes the road CRITICAL, regardless of the numbers of HEAVY or MODERATE slots.
  //two slots are HEAVY and one slot is MODERATE, one slot is LIGHT, 0 slots are severe, the road status is CONGESTED.

  if(severe>0)
  {
     printf("\nRoad Status: CRITICAL\n");
  }
  else if(heavy>=5)
  {
     printf("\nRoad Status: CONGESTED\n");
  }
  else if(moderate>=4)
  {
     printf("\nRoad Status: BUSY\n");
  }
  else
  {
     printf("\nRoad Status: NORMAL\n");
  }


}
else
        {
           printf("Slot Unavailable.");
        }
return 0;
}



/*
struct Job 
{ 
    int id;	 // Job Id 
    int dead; // Deadline of job 
    int profit; // Profit if job is over before or on deadline 
};
*/

class Solution 
{
    public:
    //Function to find the maximum profit and the number of jobs done.
    vector<int> JobScheduling(Job a[], int n) 
    { 
        // your code here
        
        sort(a,a+n, [](Job a, Job b){return a.profit>b.profit;});

   int  mx = 0;

   for(int i=0; i<n; i++)
    mx = max(mx, a[i].dead);

   vector<int> v(mx+1,0);

   int cnt=0,prof=0;

   for(int i=0; i<n; i++){

     int last = a[i].dead;

     for(int j=last; j>0; j--){

       if(v[j]==0){

         v[j] = a[i].id;
         cnt++;
         prof+=a[i].profit;
         break;
       }
     }
   }

   vector<int> ans = {cnt,prof};

   return ans;

  }
  
};

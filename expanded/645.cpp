   val[i]=k; p=i; len=k;

  } else {

   k=min(val[2*p-i], p+len-i);

   while(1) {

    if (i-k<0) break;

    if (i+k>=L) break;

    if (str[i-k]!=str[i+k]) break;

    k++;

   }

   k--;

   val[i]=k;

   if (i+k>p+len) {

    p=i; len=k;

   }

  }

 }



 j=0;

 for (i=0; i<L; i++) {

  while(str[i]!=tmp[j]) {

   j--;

   if (j<0) break;

   j=h[j];

  }

  j++;

  if (i==0) mL[i]=j;

  else {

   mL[i]=max(j, mL[i-1]);

  }

 }



 res=0;

 for (i=0; i<L; i++) {

  x=1+val[i]*2;

  j=i-val[i]-1;

  if (j>=0) x+=2*min(mL[j], L-1-(i+val[i]));

  if (res<x) {

   res=x; k=i;

  }

 }

 j=k-val[k]-1;

 if (j>=0 && min(mL[j], L-1-val[k]-k)>0) {

  x=min(mL[j], L-1-val[k]-k);

  for (i=0; i<j; i++) if (mL[i]==x) break;

  puts("3");

  printf("%d %d\n", i-x+1+1, x);

  printf("%d %d\n", k-val[k]+1, 2*val[k]+1);

  printf("%d %d\n", L-x+1, x);

 } else {

  puts("1");

  printf("%d %d\n", k-val[k]+1, val[k]*2+1);

 }

 return 0;

}

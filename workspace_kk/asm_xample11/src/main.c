extern int asm_sum(int x, int y);

int sum(int x, int y) {
	return x + y;
}


int GetFib(int n);
void morse(int fib);




int main(void) {

	int i, j;

	i = sum(1, 2);
	j = asm_sum(5, 6);

	// Enter an infinite loop, just incrementing a counter
	volatile static int loop = 0;
	while (1) {
		loop++;
	}
}



int GetFib(int n)
{
    int arr[20];
  arr[0] = 1;
  arr[1] = 1;
  int i = 0;
  for(i = 2; i<=n;i++)
  {
    arr[i] = arr[i-1] + arr[i-2];
  }
  n = arr[n-1];
  return n;
}

void morse(int fib)
{
    int incr = 0;
    int arr[4];
    while(fib > 0)
    {
        arr[incr] = fib % 10;
        fib = fib/10;
        incr++;
    }
    while(incr != 0)
    {
        switch(arr[incr])
        {
            case 0:
            //do time shit here

            break;

            case 1:
            //do time shit here
            break;

            case 2:
            //do time shit here
            break;

            case 3:
            //do time shit here
            break;
            case 4:
            //do time shit here
            break;

            case 5:
            //do time shit here
            break;

            case 6:
            //do time shit here
            break;

            case 7:
            //do time shit here
            break;

            case 8:
            //do time shit here
            break;

            case 9:
            //do time shit here
            break;

            default:
                return;
        }
        incr--;
    }
}

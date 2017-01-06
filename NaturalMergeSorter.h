#ifndef NATURALMERGESORTER_H
#define NATURALMERGESORTER_H

class NaturalMergeSorter
{
public:
    void sort(int inOut[], int size)
    {
        a = inOut;
        n = size;
        b = new int[n];
        naturalmergesort();
        inOut = a;
        delete b;
    }

private:
    int *a;
    int *b;    // Hilfsarray
    int n;

    bool mergeruns(int a[], int b[])
        {
            int i=0, k=0, x;
            bool asc=true;

            while (i<n)
            {
                k=i;
                do x=a[i++]; while (i<n && x<=a[i]);  // aufsteigender Teil
                while (i<n && x>=a[i]) x=a[i++];      // absteigender Teil
                    merge (a, b, k, i-1, asc);
                asc=!asc;
            }
            return k==0;
        }

    void merge(int a[], int b[], int lo, int hi, bool asc)
        {
            int k=asc? lo: hi;
            int c=asc? 1: -1;
            int i=lo, j=hi;

        // jeweils das nächstgrößte Element zurückkopieren,
        // bis i und j sich überkreuzen
        while (i<=j)
        {
            if (a[i]<=a[j])
                b[k]=a[i++];
            else
                b[k]=a[j--];
            k+=c;
        }
    }

    void naturalmergesort()
    {
        // abwechselnd von a nach b und von b nach a verschmelzen
        while (!mergeruns(a, b) & !mergeruns(b, a));
    }

};    // end class NaturalMergeSorter
#endif // NATURALMERGESORTER_H

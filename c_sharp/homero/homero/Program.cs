using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;

namespace homero
{
    class Program
    {
        public delegate void valtozasEvent(object sender, EventArgs e);
        class homero
        {
            public event valtozasEvent Changed;
            private List<int> adatok = null;
            private int verem_teto;             //verem tető
            public homero()     //konstruktor
            {
                verem_teto = 0; //veremtetőnek kezdőérték
                adatok = new List<int>();   //ha példányosítom az osztályt akkor automatikusan létrehozom a listát
                Changed += new valtozasEvent(ListAlarm);  //a Changed eventhez hozzáadom a valtozasEvent delegáltat aminek értékül a ListAlarm fv-t kapja meg
            }
            const int max = 30;     //riasztási fok
            public void Push(int ertek)     //feltöltési függvény
            {
                verem_teto++;
                adatok.Add(ertek);
                if(ertek>=max)      //itt lép életbe az event
                    OnChanged(EventArgs.Empty); /*Meghívom az OnChanged függvényt értékül adom az EventArgs.Empty-t
                                                 *Az OnChanged függvényben megvizsgálom hogyha a Changed igaz(vagyis hogyha a changed eventhez van rendelve valami)
                                                 *Átadjuk a Changed eventnek saját magát ezzel életbe lép a lánc reakció
                                                 *Meghívódik a ListAlarm függvény
                                                 */

            }
            public int Pull()       //előhúzum a legfelső elemet a listából
            {
                if (verem_teto == 0)
                    Console.WriteLine("Hiba a verem üres!");
                return adatok[--verem_teto];
            }
            public void OnChanged(EventArgs e)
            {
                if (Changed != null)
                {
                    Changed(this, e);
                }
            }
            private void ListAlarm(object sender, EventArgs e)
            {
                Console.WriteLine("RIASZTÁS!!! TÚL MAGAS A HŐMÉRSÉKLET");
            }
        }

        static void Main(string[] args)
        {
            homero proba = new homero();    //példányosítom a homero osztályt amelyben létrehozok 1 listát a konstruktorban
            for (int i = 0; i < 10; i++)    //10 véletlen számot generálok
            {
                Random r = new Random();    //uj random
                int szam = r.Next(50);      //értékül adás (0-50ig lehet)
                proba.Push(szam);           //feltöltés
                int szam1 = proba.Pull();   //előhuzás
                Console.WriteLine("A hőmérséklet értéke: "+szam+" Celsius fok");    //kiíratás
                Console.WriteLine(" ");
                Thread.Sleep(1000);         //1 másodperces pihi
            }
            Console.Read();     //program vége
        }
    }
}

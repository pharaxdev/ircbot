using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;

namespace reszveny
{
    class Program
    {
        public delegate void changeEvent(object sender, EventArgs e);
        class reszveny
        {
            public event changeEvent Changed;
            private int aktualis_arfolyam;
            public int Aktualis
            {
                get { return aktualis_arfolyam; }
                set { this.aktualis_arfolyam = value; }
            }
            private List<int> arlista = null;
            private int verem_teto;
            public reszveny()
            {
                verem_teto = 0;
                aktualis_arfolyam = 240;
                arlista = new List<int>();
                Changed += new changeEvent(Bejelentkezes);
            }
            public void Push(int value)
            {
                verem_teto++;
                arlista.Add(value);
                if (value < aktualis_arfolyam)
                {
                    OnChanged(EventArgs.Empty);
                }
                else
                {
                    Tulmagas(value);
                }

            }
            public int Pull()
            {
                if (verem_teto == 0)
                    Console.WriteLine("Hiba! A lista üres!");
                return arlista[--verem_teto];
            }
            public void OnChanged(EventArgs e)
            {
                if (Changed != null)
                {
                    Changed(this, e);
                }
            }
            private void Tulmagas(int value)
            {
                Console.WriteLine("Sajnos még nem elég alacsony az árfolyam a bejelentkezéshez!");
                Console.WriteLine("Jelenleg itt áll: " + value + "$ .");
                Console.WriteLine(" ");
            }
            private void Bejelentkezes(object sender, EventArgs e)
            {
                Console.Write("Bejelentkezés a megvételhez");
                for (int i = 0; i < 3; i++)
                {
                    Thread.Sleep(2000);
                    Console.Write(".");
                }
                Console.WriteLine(" ");
                Megvetel();
            }
            private void Megvetel()
            {
                Random rnd = new Random();
                int r = rnd.Next(2);
                switch (r)
                {
                    case 0:
                        Console.WriteLine("A vásárlás sikertelen, valaki gyorsabb volt!");
                        break;
                    case 1:
                        Console.WriteLine("Gratulálok sikeres volt a vétel!");
                        Cegek();
                        break;
                    default:
                        break;
                }
            }
            private void Cegek()
            {
                Random r = new Random();
                int szam = r.Next(0,1);
                switch (szam)
                {
                    case 0:
                        Console.WriteLine("Részvényese lettél az Ibron Systems vállalatnak!");
                        break;
                    case 1:
                        Console.WriteLine("Részvényese lettél az Itna Design vállalatnak!");
                        break;
                    default:
                        break;
                }
            }
        }
                
        static void Main(string[] args)
        {
            reszveny alany = new reszveny();
            Console.WriteLine("Üdvözöllek a részvény vásárló programban!");
            Console.WriteLine("Az Megadott érték " + alany.Aktualis + "$ .");
            Console.Write("Szeretnéd módosítani? (igen-nem)");
            string dontes = Convert.ToString(Console.ReadLine());
            switch(dontes)
            {
                case "igen":
                    //Console.WriteLine(" ");
                    Console.Write("Mennyire?");
                    int szamocska = Convert.ToInt16(Console.ReadLine());
                    alany.Aktualis = szamocska;
                    break;
                case "nem":
                    break;
                default: break;
            }
            int also_hatar = alany.Aktualis - 40;
            int felso_hatar = alany.Aktualis + 40;
            for (int i = 0; i < 3; i++)
                Console.WriteLine(" ");
            Thread.Sleep(2000);
            for(int i= 0;i<10;i++)
            {
                Random r = new Random();
                int szam = r.Next(also_hatar,felso_hatar);
                alany.Push(szam);
                Console.WriteLine(" ");
                Thread.Sleep(1000);
            }
            Console.ReadLine();
        }
    }
}

using System;
using System.Threading;
using System.IO;

namespace kopapirollo
{
    class Program
    {
        #region Private Variables
        private FileStream fs;
        private StreamWriter sw;
        private StreamReader sr;
        private int gepPont;
        private int emberPont;
        private bool hibas_read;
        private string[] lehetosegek = new string[] { "kő", "papír", "olló" };  //új vektor/tömb 3 elemet tartalmaz
        private const string ellenfelNeve = "Gép";    //multi rendszerhez szükséges ami később jön :D
        private const string fajl_nev = "Eredmeny.txt";
        private const string help_fajl = "Help.txt";
#endregion
        public void Start()
        {
            gepPont = 0;
            emberPont = 0;
            hibas_read = false;  //ez ahoz kell hogyha a játékos mást ír be nempedig a lehetséges megoldásokat ha true-ra változik kilép a ciklusból!
            for (int j = 0; j < 3; j++)
            {
                Console.Clear();
                Random r = new Random();    //új Random inicializálás
                int randomszam = r.Next(2); //egy változóba beleirjuk a random számot és megadom a random szám határait: r.Next(2) leforditva r egyenlő lehet 0-1-2 vel
                Console.WriteLine("Nekem már megvan az eredmény!");
                Thread.Sleep(500);     //szál altatása
                Console.Write("Most írd be, hogy te mit gondoltál!(kő, papír olló)");
                string jatekos_gondolta = Convert.ToString(Console.ReadLine());  //beolvastatjuk hogy a játékos mit választ! ezt át konvertáljuk String azaz karakter(szó) tipusra
                switch (jatekos_gondolta)    //itt ellenőrizzük h mit tartalmaz a jatekos_gondolta
                {
                    case "kő": break;   //ha "kő" kilép az ellenőrzésből JÓ megoldás
                    case "papír": break;
                    case "olló": break;
                    default: Console.WriteLine("ejnyje rosszat adtál meg!");    //ha egyiksem a beolvasott változó akkor ez lép érvénybe    
                        hibas_read = true;    //itt igazra állitjuk
                        break;
                }
                if (hibas_read)   //HA hibas_read IGAZ(=true)
                    break;  //kilépünk
                else
                {
                    for (int i = 1; i < 4; i++) //csak lazán elszámolunk 3-ig 1 másodperceket várva
                    {
                        Thread.Sleep(1000);
                        Console.WriteLine(i);
                    }
                    Console.WriteLine("GÉP: {0} JÁTÉKOS: {1}", lehetosegek[randomszam], jatekos_gondolta);   //ki iratom a választást
                    #region Equal
                    if (lehetosegek[randomszam] == jatekos_gondolta) //ha a gépáltal gondolt és a játékos által gondolt lehetőség egyenlő
                                                            //lehetosegek[randomszam]  itt a lehetosegek tömbböl kiválasztom a randomszam(0-1-2) indexű stringet
                    {
                        Console.WriteLine("Döntetlen!");
                        gepPont++;  //adunk 1-1 pontot
                        emberPont++;
                    }
                    else
                    {
                        #region//szabályok
                        if (jatekos_gondolta == "kő" && lehetosegek[randomszam] == "papír")  //HA a játékos által gondolt = a kő szócskával &&(és) lehetosegek[randomszam] = a papírral akkor!
                        {
                            Console.WriteLine("Sajnos vesztettél! A papír betakarja a követ!");
                            gepPont++;
                        }
                        if (jatekos_gondolta == "kő" && lehetosegek[randomszam] == "olló")
                        {
                            Console.WriteLine("Gratulálok győztél a kő kicsorbítja az ollót!");
                            emberPont++;
                        }
                        if (jatekos_gondolta == "papír" && lehetosegek[randomszam] == "kő")
                        {
                            Console.WriteLine("Gratulálok győztél! A papír betakarja a követ!");
                            emberPont++;
                        }
                        if (jatekos_gondolta == "papír" && lehetosegek[randomszam] == "olló")
                        {
                            Console.WriteLine("Sajnos vesztettél! Az olló szétvágja a papírt!");
                            gepPont++;
                        }
                        if (jatekos_gondolta == "olló" && lehetosegek[randomszam] == "kő")
                        {
                            Console.WriteLine("Sajnos vesztettél! A kő kicsorbítja az ollót!");
                            gepPont++;
                        }
                        if (jatekos_gondolta == "olló" && lehetosegek[randomszam] == "papír")
                        {
                            Console.WriteLine("Gratulálok győztél! Az olló szétvágja a papírt!");
                            emberPont++;
                        }
#endregion
                    }
                    #endregion
                    Thread.Sleep(3000);
                }
            }
            Console.WriteLine("A te eredményed: {0} a gép eredménye: {1}", emberPont, gepPont); //ki írom a végeredményt
            Console.Write("Add meg a neved: ");
            string jatekosNeve = Convert.ToString(Console.ReadLine());
            mentes(jatekosNeve, ellenfelNeve, emberPont, gepPont);
            Console.WriteLine("Megakarod tekinteni az eredmény listát? y/n");
            string dontes = Convert.ToString(Console.ReadLine());
            switch (dontes)
            {
                case "y": Eredmeny();
                    break;
                case "n": break;
                default: break;
            }
            Console.Read();
        }
        public void mentes(string nev_jatekos, string gep, int emberpont, int geppont)
        {
            if (File.Exists(fajl_nev))
            {
                fs = new FileStream(fajl_nev, FileMode.Append);
            }
            else
            {
                fs = new FileStream(fajl_nev, FileMode.CreateNew);
            }
            sw = new StreamWriter(fs);
            if (emberpont > geppont)
            {
                sw.WriteLine("A játékos neve: " + nev_jatekos + ", elért pontszáma: " + emberpont + ", Eredmény: Győzött!");
            }
            else if (emberpont == geppont)
            {
                sw.WriteLine("A játékos neve: " + nev_jatekos + ", elért pontszáma: " + emberpont + ", Eredmény: Döntetlen");
            }
            else
            {
                sw.WriteLine("A játékos neve: " + nev_jatekos + ", elért pontszáma: " + emberpont + ", Eredmény: Vesztett");
            }
            sw.Close();
            fs.Close();
        }
        public void Eredmeny()
        {
            Console.Beep();
            if(!File.Exists(fajl_nev))
            {
                Console.WriteLine("Sajnos, nincs még elmentve eredmény.");
                Thread.Sleep(2000);
                return;
            }
            fs = new FileStream(fajl_nev, FileMode.Open);
            sr = new StreamReader(fs);
            Console.Clear();
            string line;
            while ((line = sr.ReadLine()) != null)
            {
                Console.WriteLine(line);
            }
            Console.ReadLine();
            sr.Close();
            fs.Close();
        }
        public void Help()
        {
            Console.Beep();
            if(!File.Exists(help_fajl))
            {
                fs = new FileStream(help_fajl, FileMode.CreateNew);
                sw = new StreamWriter(fs);
                sw.WriteLine("Üdvözöllek a kő, papír, olló játkkban!");
                sw.WriteLine("A játék 3 menetből áll.");
                sw.WriteLine("A 3 menet alatt eldől, hogy ki győz.");
                sw.WriteLine("A győztes neve bekerül az Eredmenyek.txt nevű fájlba!");
                sw.WriteLine("Kellemes játékot kívánok!");
                sw.Close();
                fs.Close();
            }
            fs = new FileStream(help_fajl, FileMode.Open);
            sr = new StreamReader(fs);
            string line;
            while ((line = sr.ReadLine()) != null)
            {
                Console.WriteLine(line);
            }
            sr.Close();
            fs.Close();
            Console.ReadLine();
        }
        static void Main(string[] args)     //fő függvény ez veszi át az irányitást ha a elinditod a programot
        {
            Console.Beep();
            Program start = new Program();  //példányosítom azaz létrehozok 1 alanyt hogy megtudjam hívni a Start() fv-t
            bool kilepes = false;
            while(kilepes == false)
            {
            Console.WriteLine("(1) Játék indítása, (2) Segítség, (3) Eredmény lista, (0) Kilépés");
            string Valasztas = Convert.ToString(Console.ReadLine());
            switch (Valasztas)
            {
                case "1": start.Start();
                    break;
                case "2": start.Help();
                    break;
                case "3": start.Eredmeny();
                    break;
                case "0": kilepes = true;
                    break;
                default:
                    Console.WriteLine("Rosszat adtál meg!");
                    Thread.Sleep(1000);
                    break;
            }
            Console.Clear();
            }
            Console.Beep();
        }
    }
}

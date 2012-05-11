using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using System.Threading;




namespace Peldak
{
    #region Delegate class
    public class tesztelek                  //delegáltakhoz kell!
    {
        public static int kob(int i)
        {
            return i * i * i;   //vissza adom a kapott paraméter értékét!
        }
    }
    #endregion
    #region struct
    struct tanulo
    {
        public string nev;
        public int kor;
    }
    #endregion
    #region interface
    public interface IMandarin              //mandarin interface definiálása tuladjonságok...
    {
        bool friss();
        int mennyiseg();
    }
    #endregion
    #region Class with Interface
    public class Magyar : IMandarin          //Magyar osztályhoz hozzárendelem a mandarin(IMandarin) interfacet :P
    {
        public bool friss()                 //IMandarin
        {
            return true;
        }
        public int mennyiseg()              //IMandarin
        {
            return 20;
        }
        public Magyar()                     //Konstruktor...
        {
            Console.WriteLine("Létrehoztam egy magyar mandarint!(Magyar konstruktor!)");
            //Amikor példányosítom a Magyar osztályt akkor ezt ki is iratom!
        }
    }
    #endregion
    #region Generic class
    public class tipusok<T>              //tipus paraméterek osztály strukturak neven
    {
        T[] vektor;                         // új tömbb amely tárolja az elemeket
        int verem_teto;                     //a név magáért beszél a verem teteje :P
        public tipusok(int db)           //konstruktor amely a DB változot veszi be
        {
            vektor = new T[db];             //megadjuk hogy hány elemet tartalmazzon a tömb
            verem_teto = 0;                 //megadjuk a verem tető kezdő értékét
        }
        public void push(T t)                //feltöltő fv() amelynek a t elemet adjuk által meghiváskor :P
        {
            if (verem_teto < vektor.Length)  //vizsgálat: ha nincs tele a vektor[] tömb akkor feltöltjük
            {
                vektor[verem_teto++] = t;     //feltöltés
            }
            else
            {
                throw new Exception("Tele a verem kikéne üriteni!");    //kivétel dobása "TELE A VEREM"
            }
        }
        public T pull()                   //ezzel a fv() el hozzuk elő a verem[] legfelső elemét
        {
            if (verem_teto == 0)
                throw new Exception("Üres a verem :/ ");    //kivétel dobása ha a verem ürés
            return vektor[--verem_teto];    //vissza adom a verem legfelső elemét
        }
    }
    #endregion

    class Program
    {
        public void masodfoku()             //másodfokú egyenlet megoldása
        {
            Console.WriteLine("Kérem az A-t!");
            int a = Convert.ToInt16(Console.ReadLine());
            Console.WriteLine("Kérem a B-t!");
            int b = Convert.ToInt16(Console.ReadLine());
            Console.WriteLine("Kérem a C-t!");
            int c = Convert.ToInt16(Console.ReadLine());
            double D;                       //diszkrimináns
            D = ((b * b) - 4 * (a * c));    //diszkrimináns kiszámításának módja
            if (D > 0)
            {
                double x1 = (-b + Math.Sqrt(D)) / (2 * a);
                double x2 = (-b - Math.Sqrt(D)) / (2 * a);
                Console.WriteLine("Az x1={0}, az x2={1}!", x1, x2);
            }
            else if (D < 0) Console.WriteLine("A diszkrimináns kisebb nullánál!");
            else Console.WriteLine("A diszkrimináns nulla!");
            Console.Read();
        }
        public void structs()               //struktúra fv() meghívásakor
        {
            Console.WriteLine("Új tanuló struktúra (anonymous)");
            tanulo anonymous = new tanulo();//anonymous példány
            anonymous.nev = "Norbi";
            anonymous.kor = 16;
            Console.WriteLine("Neve: " + anonymous.nev + " Kora: " + anonymous.kor);
        }
        public void adat()                  //adatmentés
        {
            StreamWriter sw;                //sw definiálása ezzel fogom irni a fájlba a dolgokat
            ArrayList files = new ArrayList();
            files.Add("file1.txt");         //a files ArrayList feltöltése
            files.Add("file2.txt");
            files.Add("file3.txt");
            for (int i = 0; i < files.Count; i++)           //nemszükséges          JELEN ESETBEN KELL!
            {
                Console.WriteLine("Az adatok mentése folyamatban(ez igénybe vehet akár több percet is...");
                sw = File.CreateText((string)files[i]);     //sw inicializációja itt adom meg meg hogy mi is legyen a tartalma
                for (int j = 1; j <= 100000000; j++)
                {
                    sw.Write(j);
                }
                sw.Close();
            }
            Console.WriteLine("Az adatok mentése sikeres volt!");
        }
        public void matrix()                                //mátrix függvény
        {
            int[,] tm = new int[100000, 30];                //2 dimenziós tömb melynek az 1. dimenziójában: 100000 adat lesz a másodikban 30!
            int sor, oszlop;
            Random rnd = new Random();                      //új random tag
            Console.WriteLine(" ************** BELÉPÉS A MÁTRIXBA ******************");
            Console.Write("Belépés folyamatban...");
            Thread.Sleep(1000);
            Console.Write(" 5");
            Thread.Sleep(1000);
            Console.Write(" 4");
            Thread.Sleep(1000);
            Console.Write(" 3");
            Thread.Sleep(1000);
            Console.Write(" 2");
            Thread.Sleep(1000);
            Console.Write(" 1");
            Thread.Sleep(1000);
            Console.Write(" 0");

            for (sor = 0; sor < 100000; sor++)
            {
                for (oszlop = 0; oszlop < 30; oszlop++)
                {
                    tm[sor, oszlop] = rnd.Next(0, 2);       //feltöltjük random számokkal a tm[] tömböt
                    Console.Write("{0} ", tm[sor, oszlop]); //ezeket ki is iratjuk
                }
                Console.WriteLine();//uj sor ha megvan a 30as oszlop
            }
        }
        public void valto()     //választó menü
        {
            Console.WriteLine("(1)másodfokú függvény megoldása (2)struktúrák (3)interface && osztálymeghívások (4)Adat mentés (5)Mátrix (6)Delegáltak (7)Típus Paraméterek (8)Lambda (9)Events(0)EXIT");
            int mit = Convert.ToInt16(Console.ReadLine());
            Program menu = new Program();
            switch (mit)
            {
                case 1:
                    menu.masodfoku();
                    break;
                case 0:
                    break;
                case 2:
                    menu.structs();
                    break;
                case 3:
                    Magyar kinai = new Magyar();
                    Console.WriteLine("Friss-e? " + kinai.friss() + " Mennyi van belőle? " + kinai.mennyiseg() + "db");
                    Console.ReadLine();
                    break;
                case 4:
                    menu.adat();
                    break;
                case 5:
                    menu.matrix();
                    break;
                case 6:
                    menu.delegaltak();
                    break;
                case 7:
                    menu.tipus();
                    break;
                case 8:
                    menu.lambda();
                    break;
                case 9:
                    menu.eventek();
                    break;

                default:
                    Console.WriteLine("Nem jó számot adtál meg!");
                    Console.Read();
                    break;
            }
        }
        public void automatikus()       //automatizált program
        {
            Program p = new Program();
            Thread mentes = new Thread(p.adat);     //adat fv()
            Thread matrix = new Thread(p.matrix);   //matrix fv()
            mentes.Priority = ThreadPriority.Highest;   //prioritás beállítása
            matrix.Priority = ThreadPriority.Normal;    //normál prioritás
            mentes.Start();                         //adat fv() inditása
            try
            {
                matrix.Start();
            }
            catch (Exception e)                 //hiba kezelő
            {
                Console.WriteLine(e.Message);   //hiba kiírása
            }
            finally
            {
                if (mentes.ThreadState != ThreadState.Running)  //Amint befejeződik a mentes szál Abortálom a matrix szálat
                    matrix.Abort();
                if (!mentes.IsAlive && !matrix.IsAlive)
                {
                    Console.WriteLine("Kész van az adatok mentése!");
                    Console.Read();
                }
            }
        }
        delegate int szoroz(int k); //delegáltakhoz szükséges... itt definiálom értékül adom neki a K nevü szám tipusu változót
        //szoroz a DELEGÁLT!
        public void delegaltak()    //delegáltak fv()
        {
            Console.WriteLine("********** DELEGÁLTAK **********");
            Console.WriteLine("Kérek 1 számot vissza adom a köbét!");
            int mit = Convert.ToInt32(Console.ReadLine());  //bekérem a számot aminek a köbét adom vissza
            szoroz alany = new szoroz(tesztelek.kob);    //új szoroz itt példányosítom a szoroz delegáltat ALANY néven! Aminek ha paramétert adunk akkor meghivja a tesztelek osztály kob() fvét! 
            Console.WriteLine("a " + mit + " köbe: " + alany(mit)); //ki íratás!
            Console.Read();
        }
        public void tipus()         //Típus paraméterek függvény
        {
            tipusok<string> tipus = new tipusok<string>(10);     //uj tipusparaméter strukt néven STRINGel, amely 10 DBot tud tárolni!
            tipus.push("ablak");                        //feltöltés
            tipus.push("ez itt 1 tipusparaméter");      //feltöltés
            tipus.push("Alma");                         //feltöltés
            tipus.push("c#");                           //feltöltés
            tipus.push("I (l) C#");                     //feltöltés
            tipusok<int> tipint = new tipusok<int>(2);         //új típusparaméter struktint néven amely INTet képes tárolni és abbol is csak 2-t!
            tipint.push(40);  //feltöltés...
            tipint.push(20);
            try
            {
                string legfelso = tipus.pull();       //a legfelso változóba beleirom a tipus legfelső elemét
                int legfelsoint = tipint.pull();      //a legfelsoint változóba pedig a a tipint legfelső elemét!
                Console.WriteLine("A STRING tipusparaméter legfelső eleme: " + legfelso + ". Az INT tipusparaméter legfelső eleme " + legfelsoint + ".");
            }   //ki is irattam az eredményeket
            catch (Exception e)                                  //hiba kezelő
            {
                Console.WriteLine(e.Message);                   //hiba kiírása
            }
            finally
            {
                Console.WriteLine("Kész vagyunk a Típus paraméterekkel!");
                Console.Read();
            }
            /*Tehát a TípusParaméterek fő tulajdonsága hogy a kód újra hasznosítható
             * mint például a fenti eset
             * másik lényeges tulajdonság hogy futási időben adunk neki értéket
             */
        }
        public delegate T Mandarinfa<T, P, P1>(P p, P1 p1);       //saját delegált a lambda fv() hez amely TIPUSPARAMÉTERES delegált (T) 
        // T olyan tipus lesz amit később megadunk :P , P p és P1 p1 pedig 2 paraméter amely a visszatérési értékhez kell
        public void lambda()                                //lambda fv()
        {
            Mandarinfa<string, string, bool> fa = (x, y) =>    //létrehozok 1 példányt a Mandarinfa delegáltnak FA néven melyben (int,string,bool lesz) x és y változókat adja vissza
            {
                if (y) return "friss";          //Ha y igaz értéket kap (true,1 stb)
                else return "nem friss";        //ha y hamis értéket kap
            };
            string nyar = fa("nyári", true);       //nyar változóba létrehozok 1 új fát (amely nyári és igaz jelzőt kapja)
            Console.WriteLine(nyar);            //ki íratom
            Console.Read();
        }
        #region EVENT
        public delegate void ChangedEventHandler(object sender, EventArgs e);
        /*új delegált EVENTHEZ kell két értéke van
         * az első az az objektum amely kiváltotta az eseményt
         * a második pedig az eseményhez kapcsolódó információk
         * a második paraméter csak olyan tipus lehet mely az EventArgs  osztályból származik!
         */
        class MyListWithEvent
        {
            private List<int> list = null;              //privát List<int> tipusu változó KEZDŐértéke nulla
            public event ChangedEventHandler Changed;   //új event ChangedEventHandler delegálthoz tartozó és Changed a neve!
            public MyListWithEvent()    //konstruktor
            {
                list = new List<int>(); //a list változónak értéket adunk(új List<int>()-et)
            }
            public void Add(int value)
            {
                list.Add(value);        /*public delegate void ChangedEventHandler(object kuldo, EventArgs e);
                                         * ebből a object kuldo a lenyeges...
                                         */
                OnChanged(EventArgs.Empty); // ezt adja vissza
            }
            protected virtual void OnChanged(EventArgs e)   //OnChanged fv Eventargs e-t adja át
            {
                if (Changed != null)        //ha a Changed event (public event ChangedEventHandler Changed;) nem null
                {
                    Changed(this, e);       //a Changed eventet meghívja saját maga és az EventArgs e értékével!
                }
            }
        }
        class ListListener
        {
            private MyListWithEvent list = null;    // létrehozunk egy MyListWithEvent tipusu változót amely felveszi a null kezdőértéket
            public ListListener(MyListWithEvent l)  //konstruktor MyListWithEvent l nevü változójával
            {
                list = l;                           //listnek értékül adja az l értéket
                list.Changed += new ChangedEventHandler(ListChanged);
                //a Changed eventhez hozzáadom a ListChanged fv-t! (ChangedEventHandler 1 delegált!)
                //Amint hozzáadok a listhez egyböl érvénybe lép az EVENT meghivásra kerül a ListChanged fv()
            }
            public void Add(int value)
            {
                list.Add(value);
            }
            private void ListChanged(object sender, EventArgs e) //ListChanged fv()
            {
                Console.WriteLine("A lista megváltozott...");
            }
        }
        public void eventek()
        {
            MyListWithEvent list = new MyListWithEvent();   //példányosítom a MyListWithEvent osztályt list néven
            ListListener listlistener = new ListListener(list);//példányosítom a ListListener osztályt listlistener néven amely megkapja a listet értékként
            listlistener.Add(10);  //Hozzáadok a Listához 10et igy megváltozik a lista ÉRVÉNYBE lép a Changed EVENT meghivodik a ListChanged fv! 
            listlistener.Add(20);
            Console.ReadKey();
        }
        #endregion

        static void Main(string[] args) //fő függvény
        {
            //első választási lehetőség
            Console.WriteLine("(1)Manuális (2)Automatikus (többszálasított) (0)Exit");
            int teszt = Convert.ToInt16(Console.ReadLine());
            switch (teszt)                  //választás
            {
                case 1:
                    Program manually = new Program();
                    manually.valto();
                    break;
                case 2:
                    Program automate = new Program();
                    automate.automatikus();
                    break;
                case 0:
                    break;
                default:                    //ha nem a meglevőket választotta(1-2)
                    Console.WriteLine("Rossz számot adtál meg!");
                    break;
            }



        }
    }
}
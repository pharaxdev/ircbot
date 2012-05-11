program automata;
uses crt;
type rekesz=record
        sorszam:byte;
        db:byte;
        ar:integer;
end;
type vasarlas=record
        rekesz:byte;
        db:byte;
        _1,_2,_5,_10,_20,_50,_100:byte;
end;
var     n_rekesz,n_vasarlas:byte;
        csoki:array[1..100] of rekesz;
        vek:array[1..100] of vasarlas;
procedure elso_feladat;
var     f:text;
        i:byte;
begin
        assign(f,'csoki.txt');
        reset(f);
        readln(f,n_rekesz);
        for i:=1 to n_rekesz do
                readln(f,csoki[i].sorszam,csoki[i].db,csoki[i].ar);
        close(f);
        assign(f,'vasarlas.txt');
        reset(f);
        readln(f,n_vasarlas);
        for i:=1 to n_vasarlas do
                readln(f,vek[i].rekesz,vek[i].db,vek[i]._1,vek[i]._2,vek[i]._5,vek[i]._10,vek[i]._20,vek[i]._50,vek[i]._100);
        close(f);
end;
procedure masodik_feladat;
var     i:byte;
        ossz:longint;
begin
        ossz:=0;
        for i:=1 to n_rekesz do
                ossz:=ossz+(csoki[i].db*csoki[i].ar);
        writeln('2. feladat');
        writeln('Az automat ban ',ossz,' fabatka ‚rt‚kû csokol d‚ van.');
end;
procedure harmadik_feladat;
var     i:byte;
        hz:set of byte;
begin
        hz:=[];
        writeln('3. feladat');
        for i:=1 to n_vasarlas do
                hz:=hz+[vek[i].rekesz];
        for i:=1 to n_rekesz do
                if i in hz then
                        write(i,' ');
        writeln;
end;
procedure negyedik_feladat;
var     i:byte;
        ertek:longint;
begin
        writeln('4. feladat');
        writeln('K‚rem a p‚nz”sszeget!');
        readln(ertek);
        for i:=1 to n_rekesz do
        begin
                if (csoki[i].db>=7) and ((csoki[i].ar*7)<=ertek) then write(i,' ');
        end;
        writeln;
end;
procedure otodik_feladat;
var     i:byte;
        _rekesz:byte;
        db:integer;
        ar:longint;
        n1,n2,n5,n10,n20,n50,n100:integer;
begin
        n1:=0; n2:=0; n5:=0; n10:=0; n20:=0; n50:=0; n100:=0;
        writeln('5. feladat');
        writeln('Adja meg a rekesz sz mot');
        readln(_rekesz);
        if (_rekesz >0) and (_rekesz <= n_rekesz) then
                begin
                        writeln('Adja meg a darabsz mot!');
                        readln(db);
                        ar:=csoki[_rekesz].ar*db;
                        while ar>0 do
                        begin
                                if ar > 100 then begin n100:=n100+1; ar:=ar-100; end
                                else if (ar>=50) and (ar<100) then begin n50:=n50+1; ar:=ar-50; end
                                else if (ar >= 20) and (ar < 50) then begin n20:=n20+1; ar:=ar-20; end
                                else if (ar >= 10) and (ar < 20) then begin n10:=n10+1; ar:=ar-10; end
                                else if (ar >= 5) and (ar < 10) then begin n5:=n5+1; ar:=ar-5; end
                                else if (ar >= 2) and (ar < 5) then begin n2:=n2+1; ar:=ar-2; end
                                else begin n1:=n1+1; ar:=ar-1; end;
                        end;
                        if n100>0 then writeln('100 ',n100);
                        if n50>0 then writeln('50 ',n50);
                        if n20>0 then writeln('20 ',n20);
                        if n10>0 then writeln('10 ',n10);
                        if n5>0 then writeln('5 ',n5);
                        if n2>0 then writeln('2 ',n2);
                        if n1>0 then writeln('1 ',n1);
                end
        else
                writeln('Hib s rekeszsz m!');
end;
procedure hatodik_feladat;
var     i:byte;
        db:integer;
        f:text;
        ossz:longint;
begin
        db:=csoki[7].db;
        assign(f,'rekesz7.txt');
        rewrite(f);
        for i:=1 to n_vasarlas do
        begin
                if vek[i].rekesz=7 then
                begin
                        ossz:=(vek[i]._100*100)+(vek[i]._50*50)+(vek[i]._20*20)+(vek[i]._10*10)+(vek[i]._5*5)+(vek[i]._2*2)+(vek[i]._1*1);
                        if (db >= vek[i].db) and (ossz>= (vek[i].db*csoki[7].ar)) then
                        begin
                                writeln(f,i,#9,vek[i].db);
                                db:=db-vek[i].db;
                        end
                        else
                        begin
                                if (ossz< (vek[i].db*csoki[7].ar)) then writeln(f,i,#9,'nem volt eleg penz')
                                else if (db<vek[i].db) then writeln(f,i,#9,'keves a csoki');

                        end;
                end;
        end;
        close(f);
end;
begin
clrscr;
elso_feladat;
masodik_feladat;
harmadik_feladat;
negyedik_feladat;
otodik_feladat;
hatodik_feladat;

readln;

end.
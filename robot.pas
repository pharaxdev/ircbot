program robot;
uses crt;
var     n:byte;
        asd:string;
        programok:array[1..100] of string[200];
        vek:array[1..100] of string[200];
procedure elso_feladat;
var     i:byte;
        f:text;
begin
        assign(f,'program.txt');
        reset(f);
        readln(f,n);
        for i:=1 to n do readln(f,programok[i]);
        writeln(programok[i]);
        close(f);
end;
function ellentett(kar:char):char;
begin
        case kar of
        'E': ellentett:='D';
        'K': ellentett:='N';
        'D': ellentett:='E';
        'N': ellentett:='K';
end;
end;
type position=record
        x,y:integer;
end;
function tavolsag(x,y:integer):real;
begin
        tavolsag:=sqrt(sqr(x)+sqr(y));
end;
procedure masodik_feladat;
var     i,j:integer;
        utasitas:byte;
        lehet:boolean;
        pos:position;
        tav:real;
        max:position;
        sorszam:byte;
begin
        for i:=1 to n do vek[i]:=programok[i];
        writeln('2. feladat');
        writeln('K‚rem adja meg az utas¡t ssor sz m t!');
        readln(utasitas);
        lehet:=false;
        if (utasitas <1) or (utasitas > n) then
                writeln('Hib s ‚rt‚k')
        else
        begin
                for i:=1 to length(programok[utasitas])-1 do
                begin
                        if ellentett(programok[utasitas][i]) = programok[utasitas][i+1] then
                        begin
                                lehet:=true;
                                delete(vek[utasitas],i,2);
                        end;
                end;
        end;
        if lehet then writeln('egyszerûs¡thet‹') else writeln('nem egyszerûs¡thet‹');
        pos.x:=0;
        pos.y:=0;
        max.x:=0;
        max.y:=0;
        tav:=tavolsag(pos.x,pos.y);
        sorszam:=0;
        for i:=1 to length(vek[utasitas]) do
        begin
                case vek[utasitas][i] of
                'E':    pos.y:=pos.y+1;
                'D':    pos.y:=pos.y-1;
                'K':    pos.x:=pos.x+1;
                'N':    pos.x:=pos.x-1;
                end;
                if tavolsag(pos.x,pos.y)> tav then
                begin
                        sorszam:=i;
                        tav:=tavolsag(pos.x,pos.y);
                end;
        end;
        writeln(abs(pos.y),' l‚p‚st kell tenni az ED, ',abs(pos.x),' l‚p‚st a KN tengely ment‚n');
        writeln(sorszam,' ',tav:2:3);
end;
procedure harmadik_feladat;
var     i,j:integer;
        akku:integer;
begin
        writeln('3. feladat');
        for i:=1 to n do
        begin
                akku:=3;
                for j:=2 to length(programok[i]) do
                begin
                        if programok[i][j] <> programok[i][j-1] then
                                akku:=akku+3
                        else akku:=akku+1;
                end;
                if akku <=100 then write(i,' ');
        end;
        writeln;
end;
procedure negyedik_feladat;
var     f:text;
        i,j:integer;
        count:integer;
        k:integer;
        seged:string;
begin
        assign(f,'ujprog.txt');
        rewrite(f);
        for i:=1 to n do
        begin
                seged:=programok[i];
                seged:=seged+'$';
                count:=1;
                for j:=2 to length(seged) do
                begin
                        if seged[j] = seged[j-1] then inc(count)
                        else
                        begin
                                if count > 1 then write(f, count);
                                write(f,seged[j-1]);
                                count:=1;
                        end;
                end;
                writeln(f);
        end;
        close(f);
end;
procedure otodik_feladat;
var     i,j:integer;
        ut:string;
        szams:string;
        szam,hiba:integer;
begin
        writeln('5. feladat');
        writeln('K‚rek egy £j form tum£ utas¡t ssort!');
        readln(ut);
        szams:='';
        for i:=1 to length(ut) do
        begin
                if ut[i] in ['E','D','N','K'] then
                begin
                        val(szams,szam,hiba);
                        if szam=0 then szam:=1;
                        for j:=1 to szam do
                                write(ut[i]);
                        szams:='';
                end
                else szams:=szams+ut[i];
        end;
        writeln;
end;
begin
clrscr;
elso_feladat;
masodik_feladat;
harmadik_feladat;
negyedik_feladat;
otodik_feladat;
readln;
end.

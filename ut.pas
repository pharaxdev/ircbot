program ut;
uses crt;
type auto=record
        h,min,sec:byte;
        ido_alatt:integer;
        ido:longint;
        honnan:string;
end;
var     n:integer;
        vek,c_vek:array[1..2000] of auto;
procedure elso_feladat;
var     f:text;
        i:integer;
begin
        assign(f,'forgalom.txt');
        reset(f);
        readln(f,n);
        for i:=1 to n do
        begin
                readln(f,vek[i].h,vek[i].min,vek[i].sec,vek[i].ido_alatt,vek[i].honnan);
                delete(vek[i].honnan,1,1);
        end;
        close(f);
end;
procedure masodik_feladat;
var     i:integer;
begin
        writeln('2. feladat');
        writeln('Adja meg hanyadik j†rm˚ ir†ny†ra k°v†ncsi');
        readln(i);
        if (i>=1 ) and (i<=n) then
                if vek[i].honnan = 'A' then writeln('Felsãv†rosba halad')
                else writeln('Als¢v†rosba halad')
        else    writeln('Hib†s sz†m');
end;
function masodperc(var h,m,s:byte):longint;
begin
        masodperc:=((h*3600)+(m*60)+s);
end;
procedure harmadik_feladat;
var     i,j,count:integer;
        csere:auto;
        elso,masodik:integer;
begin
        count:=0;
        i:=0;
        while count=0 do
        begin
        i:=i+1;
        if vek[i].honnan='A' then count:=1;
        end;
        elso:=i;
        masodik:=i;
        for i:=1 to n do
                if (masodperc(vek[i].h,vek[i].min,vek[i].sec)>masodperc(vek[elso].h,vek[elso].min,vek[elso].sec)) and (vek[i].honnan='A')
                then
                begin
                        masodik:=elso;
                        elso:=i;
                end;
        writeln('3. feladat');
        writeln(masodperc(vek[elso].h,vek[elso].min,vek[elso].sec)-masodperc(vek[masodik].h,vek[masodik].min,vek[masodik].sec),' m†sodperc kÅlînbsÇggel Çrte el az £tszakasz kezdetÇt a kÇt j†rm˚');

                {
        for i:=1 to n do c_vek[i]:=vek[i];
        for i:=n downto 1 do
        for j:=1 to i-1 do
        begin
        elso:=masodperc(c_vek[j].h,c_vek[j].min,c_vek[j].sec);
        masodik:=masodperc(c_vek[j+1].h,c_vek[j+1].min,c_vek[j+1].sec);
                if elso < masodik then
                begin
                csere:=c_vek[j+1];
                c_vek[j+1]:=c_vek[j];
                c_vek[j]:=csere;
                end;
        end;
        count:=0;     }

end;
procedure negyedik_feladat;
var     orak:array[1..24] of integer;
        also,felso:integer;
        i,j:integer;
begin
        for i:=1 to 24 do
        begin
                also:=0;
                felso:=0;
                for j:=1 to n do
                begin
                        if vek[j].h=i then
                        begin
                                if vek[j].honnan='A' then also:=also+1
                                else felso:=felso+1;
                        end;
                end;
                if (also <>0) and (felso <> 0) then
                        writeln(i:2,' ',also:3,' ',felso:3);
        end;
end;
procedure otodik_feladat;
var     i,j:integer;
        csere:auto;

begin
        for i:=1 to n do c_vek[i]:=vek[i];
        for i:=n downto 1 do
        for j:=1 to i-1 do
                if c_vek[j].ido_alatt<c_vek[j+1].ido_alatt then
                begin
                        csere:=c_vek[j+1];
                        c_vek[j+1]:=c_vek[j];
                        c_vek[j]:=csere;
                end;
        for i:=1 to 10 do
                if (c_vek[i].honnan='A') then
                writeln(c_vek[i].h,':',c_vek[i].min,':',c_vek[i].sec,' Als¢')
                else
                writeln(c_vek[i].h,':',c_vek[i].min,':',c_vek[i].sec,' Felsã')
end;
procedure hatodik_feladat;
var     also:array[1..2000] of auto;
        i,j:integer;
        sajat,elozo:longint;
        f:text;
begin
        for i:=1 to n do vek[i].ido:=masodperc(vek[i].h,vek[i].min,vek[i].sec);
        elozo:=0;
        assign(f,'also.txt');
        rewrite(f);
        for i:=1 to n do
                if vek[i].honnan='F' then
                begin
                        sajat:=vek[i].ido+vek[i].ido_alatt;
                        if elozo > sajat then sajat:=elozo;
                        writeln(f,sajat DIV 3600,' ',(sajat div 3600) mod 60,' ', sajat mod 60);
                        elozo:=sajat;
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

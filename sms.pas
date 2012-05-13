program sms;
uses crt;
type rsms=record
        h,min:byte;
        tel:string[9];
        szoveg:string[100];
end;
var     vek:array[1..100] of rsms;
        n:integer;
procedure elso_feladat;
var     f:text;
        i:integer;
        seged:string;
        h,min:integer;
begin
        assign(f,'sms.txt');
        reset(f);
        readln(f,n);
        for i:=1 to n do
        begin
                readln(f,vek[i].h,vek[i].min,seged);
                delete(seged,1,1);
                vek[i].tel:=seged;
                readln(f,vek[i].szoveg);
        end;
        close(f);
        writeln(vek[i].szoveg);
        writeln(vek[i].tel);
end;
procedure masodik_feladat;
var     i:integer;
begin
        if n>10 then writeln(vek[10].szoveg)
        else writeln(vek[n-1].szoveg);
end;
procedure harmadik_feladat;
var     i,j:integer;
        min,max:integer;
begin
        min:=1;
        max:=1;
        for i:=1 to n do
        begin
                if length(vek[i].szoveg)<length(vek[min].szoveg) then min:=i;
                if length(vek[i].szoveg)>length(vek[max].szoveg) then max:=i;
        end;
        writeln('3. feladat');
        writeln('Legr”videbb zenet:');
        writeln(vek[min].h,' ',vek[i].min,' ',vek[min].tel);
        writeln(vek[min].szoveg);
        writeln('Leghosszabb zenet:');
        writeln(vek[max].h,' ',vek[max].min,' ',vek[max].tel);
        writeln(vek[max].szoveg);
end;
procedure negyedik_feladat;
var     i:integer;
        n20,n40,n60,n80,n100:byte;
begin
        n20:=0; n40:=0; n60:=0; n80:=0; n100:=0;
        for i:=1 to n do
        begin
                case length(vek[i].szoveg) of
                1..20:  inc(n20);
                21..40: inc(n40);
                41..60: inc(n60);
                61..80: inc(n80);
                81..100:inc(n100);
                end;
        end;
        writeln('4. feladat');
        writeln('1-20:',n20);
        writeln('21-40:',n40);
        writeln('41-60:',n60);
        writeln('61-80:',n80);
        writeln('81-100:',n100);
end;
procedure otodik_feladat;
var     i,j:integer;
        count1,count2:integer;
        c_vek:array[1..100] of rsms;
begin
        for i:=1 to n do c_vek[i]:=vek[i];
        count1:=0;
        count2:=0;
        for i:=1 to 24 do
        begin
                for j:=1 to n do
                begin
                        if c_vek[i].h=(i-1) then count1:=count1+1;
                end;
                if count1>10 then count2:=count2+(count1-10);
                count1:=0;
        end;
        writeln('5. feladat:');
        writeln(count2,' db sms elolvas s hoz kellene felh¡vnia a szolg ltat¢t!');
end;
function ttido(h,min:integer):longint;
begin
        ttido:=(h*60)+(min);
end;
procedure hatodik_feladat;
var     i,j:integer;
        ido:longint;
        lko,lke:integer;
        count:integer;
        bno:array[1..100] of rsms;
        k:integer;
        temp:longint;
begin
        ido:=0;
        k:=0;
        for i:=1 to n do
                if vek[i].tel='123456789' then
                begin
                        k:=k+1;
                        bno[k]:=vek[i];
                end;
        writeln('-----------------------');
        for i:=1 to k do
                writeln(bno[i].h,':',bno[i].min);
        writeln('-----------------------');
        if k>1 then
        begin
        lko:=1;
        lke:=2;
        ido:=(ttido(bno[lke].h,bno[lke].min))-ttido(bno[lko].h,bno[lko].min);
        for i:=2 to k do
        begin
                temp:=ttido(bno[i].h,bno[i].min)-ttido(bno[i-1].h,bno[i-1].min);
                if temp>ido then
                begin
                        ido:=temp;
                        lko:=i-1;
                        lke:=i;
                end;
        end;
        writeln('6. feladat');
        writeln('**********************');
        writeln(ido);
        writeln(bno[lko].h,':',bno[lko].min);
        writeln(bno[lke].h,':',bno[lke].min);
        writeln('**********************');
        write(ido DIV 60,' ¢ra ‚s ');
        writeln(ido mod 60,' perc telt el.');
        end
        else writeln('nincs elegend‹ zenet');

end;

procedure hetedik_feladat;
var     i,j:integer;
        csere:rsms;
        h,min:integer;
        tel:string[9];
        szoveg:string[100];
begin
        writeln('7. feladat');
        writeln('àra:Perc');
        readln(h,min);
        writeln('Tel:');
        readln(tel);
        writeln('Sz”veg');
        readln(szoveg);
        vek[n+1].h:=h;
        vek[n+1].min:=min;
        vek[n+1].tel:=tel;
        vek[n+1].szoveg:=szoveg;
        for i:=n downto 1 do
        for j:=1 to i-1 do
                if ttido(vek[j].h,vek[j].min)>ttido(vek[j+1].h,vek[j+1].min) then
                begin
                        csere:=vek[j+1];
                        vek[j+1]:=vek[j];
                        vek[j]:=csere;
                end;
        n:=n+1;
end;
procedure nyolcadik_feladat;
var     vek2:array[1..100] of rsms;
        i,j:integer;
        f:text;
        csere:rsms;
begin
        assign(f,'smski.txt');
        rewrite(f);
        for i:=1 to n do
        begin
                vek2[i]:=vek[i];
        end;
        for i:=n downto 1 do
        for j:=1 to i-1 do
                if vek2[j].tel>vek2[j+1].tel then
                begin
                        csere:=vek2[j+1];
                        vek2[j+1]:=vek2[j];
                        vek2[j]:=csere;
                end;
        for i:=1 to n do
        begin
                if vek2[i].tel <> '$' then
                begin
                        writeln(f,vek2[i].tel);
                        writeln(f,vek2[i].h,' ',vek2[i].min,' ',vek2[i].szoveg);
                        for j:=i+1 to n do
                        begin
                                if vek2[j].tel=vek2[i].tel then
                                begin
                                        writeln(f,vek2[j].h,' ',vek2[j].min,' ',vek2[j].szoveg);
                                        vek2[j].tel:='$';
                                end;
                        end;
                        writeln(f,'***********************************');
                end;
        end;
        close(f);
end;
procedure teszt;
var     h,min,sec:integer;
        ido:longint;
begin
        write('K‚rek egy id‹pontot sz¢k”z”kkel elv lasztva');
        readln(h,min,sec);
        ido:=((h*3600)+(min*60)+sec);
        write(ido DIV 3600,':');
        writeln((ido div 60) mod 60,':', ido mod 60);
        readln;
end;
begin
clrscr;
teszt;
elso_feladat;
masodik_feladat;
harmadik_feladat;
negyedik_feladat;
otodik_feladat;
hatodik_feladat;
hetedik_feladat;
nyolcadik_feladat;
readln;
end.
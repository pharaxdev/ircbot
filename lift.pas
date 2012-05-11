program lift;
uses crt;
type igeny=record
        ido:longint;
        cs_sorszam:byte;
        indulo,erkezo:byte;
end;
var     n_szint,n_csapat,n_igenyek:byte;
        igenyek:array[1..100] of igeny;
        lift_szint:integer;
        rndcsapat:byte;
procedure elso_feladat;
var     h,min,sec:byte;
        f:text;
        i:byte;
begin
        assign(f,'igeny.txt');
        reset(f);
        readln(f,n_szint); readln(f,n_csapat); readln(f,n_igenyek);
        for i:=1 to n_igenyek do
        begin
                readln(f,h,min,sec,igenyek[i].cs_sorszam,igenyek[i].indulo,igenyek[i].erkezo);
                igenyek[i].ido:=((h*3600)+(min*60)+sec);
        end;
        close(f);
end;
procedure masodik_feladat;
begin
        writeln('2. fealadat KÇrem a lift indul†si helyÇt');
        readln(lift_szint);
        if (lift_szint<0) or (lift_szint>n_szint) then
        begin
                writeln('Hib†s emelet sz†m, be†ll°t†s alapÇrtelmezett szintre: ',igenyek[1].indulo);
                lift_szint:=igenyek[1].indulo;
        end;

end;
procedure harmadik_feladat;
begin
        writeln('3. feladat');
        writeln('A lift a ',igenyek[n_igenyek].erkezo,'. szinten †ll az utols¢ igÇny teljes°tÇse ut†n');
end;
procedure negyedik_feladat;
var     min,max:byte;
        i:byte;
begin
        min:=lift_szint;
        max:=lift_szint;
        for i:=1 to n_igenyek do
        begin
                if igenyek[i].indulo < min then min:=igenyek[i].indulo;
                if igenyek[i].erkezo < min then min:=igenyek[i].erkezo;
                if igenyek[i].indulo > max then max:=igenyek[i].indulo;
                if igenyek[i].erkezo > max then max:=igenyek[i].erkezo;
        end;
        writeln('4. feladat');
        writeln('A legalacsonyabb szint amit Çrintett a lift: ',min);
        writeln('A legmagasabb szint amit Çrintett a lift: ',max);
end;
procedure otodik_feladat;
var     utassal,utasnelkul:integer;
        i:byte;
begin
        utassal:=0;
        utasnelkul:=0;
        if igenyek[i].indulo > lift_szint then utasnelkul:=utasnelkul+1;
        if igenyek[i].erkezo > igenyek[i].indulo then utassal:=utassal+1;
        for i:=2 to n_igenyek do
        begin
                if igenyek[i].indulo > igenyek[i-1].erkezo then utasnelkul:=utasnelkul+1;
                if igenyek[i].erkezo > igenyek[i].indulo then utassal:=utassal+1;
        end;
        writeln('5. feladat');
        writeln('Utassal: ',utassal,' alkalommal indult felfelÇ a lift');
        writeln('Utas nÇlkÅl: ',utasnelkul,' alkalommal indult felfelÇ a lift');
end;
procedure hatodik_feladat;
var     i:byte;
        hz:set of byte;
begin
        writeln('6. feladat');
        hz:=[];
        for i:=1 to n_igenyek do
                hz:=hz+[igenyek[i].cs_sorszam];
        for i:=1 to n_csapat do
                if not(i in hz) then write(i,' ');
        writeln;
end;
procedure hetedik_feladat;
var     i:byte;
        elozo,jelenlegi:byte;
        sertes:boolean;
begin
        rndcsapat:=random(n_csapat);
        elozo:=0;
        jelenlegi:=0;
        i:=0;
        sertes:=false;
        writeln('7. feladat');
        writeln('Csapat sorsz†m: ',rndcsapat);
        while elozo=0 do
        begin
                i:=i+1;
                if igenyek[i].cs_sorszam=rndcsapat then begin elozo:=igenyek[i].indulo; jelenlegi:=elozo; end;
        end;
        for i:=1 to n_igenyek do
        begin
                if igenyek[i].cs_sorszam=rndcsapat then
                begin
                        if igenyek[i].indulo <> elozo then
                        begin
                        sertes:=true;
                        writeln('Szab†ly sÇrtÇs: ',elozo,'-',igenyek[i].indulo,' emeletek kîzîtt');
                        elozo:=igenyek[i].indulo;
                        jelenlegi:=igenyek[i].erkezo;
                        end
                        else
                        begin
                        elozo:=igenyek[i].indulo;
                        jelenlegi:=igenyek[i].erkezo;
                        end;
                end;
        end;
        if sertes=false then writeln('Nem bizony°that¢ szab†lytalans†g');
end;
procedure nyolcadik_feladat;
var     szoveg:string;
        i:byte;
        fkod:byte;
        f:text;
begin
        assign(f,'blokkol.txt');
        rewrite(f);
        for i:=1 to n_igenyek do
        begin
                if igenyek[i].cs_sorszam=rndcsapat then
                begin
                        write(f,'Befejezes ideje: ');
                        write(f,igenyek[i].ido DIV 3600);
                        writeln(f,':',(igenyek[i].ido div 3600) mod 60,':',igenyek[i].ido mod 60);
                        writeln('Elozo feladat sikeressege?');
                        readln(szoveg);
                        writeln(f,'Sikeresseg: ',szoveg);
                        writeln(f,'-----');
                        writeln(f,'Indulasi emelet: ',igenyek[i].indulo);
                        writeln(f,'Celemelet: ',igenyek[i].erkezo);
                        writeln('Kovetkezo feladat kodja?');
                        readln(fkod);
                        if (fkod < 1) or (fkod>99) then
                        begin
                        writeln('Hib†s k¢d alapÇrtelmezett haszn†lata(0)');
                        writeln(f,'Feladatkod: ',0);
                        end
                        else writeln(f,'Feladatkod : ',fkod);
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
randomize;
hetedik_feladat;
nyolcadik_feladat;
readln;
end.
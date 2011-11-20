unit Level;

interface

uses classes, animation;

type
    TLevel = class (TObject)

    private
        fWidth, fHeight: Integer;
        fitems : TStringList;
        version: string;
        fDefaultGun,fDefaultGround: TAnimation;
    public
        property Width: Integer read fWidth;
        property Height: Integer read fHeight;
        property Items : TStringList read fitems;
        property DefaultGun : TAnimation read fDefaultGun;
        property DefaultGround : TAnimation read fDefaultGround;
        constructor create;
        destructor destroy; override;
        procedure loadFromFile (filename: string);
    end;

implementation

uses main, sysutils, Dialogs,
     levelObject, lvObjEnemy, lvObjBgChange, lvObjBlankScreen, lvObjConstruction,
     lvObjMessage, lvObjBonusGunChange, lvObjBonusOther;

constructor TLevel.create;
begin
     inherited create;
     fitems := TStringList.create;
     fDefaultGun := TAnimation.create;
     fDefaultGround := TAnimation.create;
     fwidth := 0;
     fheight := 100;
end;

destructor TLevel.destroy;
begin
     if (fitems<>nil) then fitems.Destroy;
     fDefaultGun.destroy;
     fDefaultGround.destroy;
     inherited destroy;
end;

procedure TLevel.loadFromFile (filename: string);
var
   tempList, paramsList: TStringList;
   i: integer;
   dir: string;
   levelObject : TLevelObject;
   yPos: Real;
begin
     //Allocate memory
     tempList := TStringList.create;
     paramsList := TStringList.create;
     tempList.LoadFromFile(filename);
     //Check header
     if (tempList.count<5) then begin
        tempList.Destroy;
        raise Exception.create ('Level file is invalid, has less than 5 lines!');
     end;
     version := tempList.Strings[0];
     fWidth := StrToInt(tempList.Strings[1]);
     //load default ground
     dir := frmMain.appdir+'images\grounds\'+tempList.Strings[2];
     fDefaultGround.loadFromDir(dir);
     //load default gun
     dir := frmMain.appdir+'images\munition\'+tempList.Strings[3];
     fDefaultGun.loadFromDir(dir);
     //Read the file it self
     yPos := 0;
     for i := 4 to tempList.count-1 do begin
         paramsList.CommaText := tempList.Strings[i];
         levelObject := nil;
         case paramsList.Strings[0][1] of //first character
              '#':; //Comment, ignore it
              '0': //Enemy
                   levelObject := TLvObjEnemy.create(Round(yPos), paramsList);
              '1': //y position delay
                   yPos := yPos + (StrToInt(paramsList.Strings[1])*20/(50*5));
              '2': //Blank screen
                   levelObject := TLvObjBlankScreen.create(Round(yPos), paramsList);
              '3': //Background Change
                   levelObject := TLvObjBgChange.create(Round(yPos), paramsList);
              '4': //Message
                   levelObject := TLvObjMessage.create(Round(yPos), paramsList);
              '5': //Construction
                   levelObject := TLvObjConstruction.create(Round(yPos), paramsList);
              '6': //Bonus troca de tiro
                   levelObject := TLvObjBonusGunChange.create(Round(yPos), paramsList);
              '7': //Bonus other
                   levelObject := TLvObjBonusOther.create(Round(yPos), paramsList);
              else begin
                   frmMain.memoLog.lines.Add('This line from level was not understood: "'+tempList.Strings[i]+'"');
                   ShowMessage ('This line from level was not understood: "'+tempList.Strings[i]+'"');
              end;
         end;
         fheight := Round(yPos) + defaultGround.Height; 
         if levelObject<> nil then
            fItems.AddObject(paramsList.Strings[1], levelObject);
         frmMain.memoLog.Lines.Add (tempList.Strings[i]);
     end;

     //Deallocate memory
     tempList.Destroy;
     paramsList.Destroy;
end;

end.













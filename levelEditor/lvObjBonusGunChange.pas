unit lvObjBonusGunChange;

interface

uses classes, windows, levelObject, lvObjAnimated;

type
    TLvObjBonusGunChange = class (TLvObjAnimated)
    private
    protected
        fModID:  string;
    public
        function readHeight : integer; override;
        function readWidth : integer; override;
        constructor create(yPos: integer; params: TStringList);
        destructor destroy; override;
        property ModID: string read fModID write fModID;
    end;

implementation

uses main, sysutils, dialogs;

constructor TLvObjBonusGunChange.create(yPos: integer; params: TStringList);
begin
     inherited create(yPos, params);
     animation.loadFromDir(frmMain.AppDir+'images\guns\'+params[2]);
     fModID := params[3];
     setScreenSideUsingInteger(StrToInt(params[4]));
     fPos.x  := StrToInt(params[5]);
     fDirX := StrToInt(params[6]);
     fDirY := StrToInt(params[7]);
     fEnergy := StrToInt(params[7]);
     fColision := true;
     fVX     := StrToInt(params[8]);
     fVY     := StrToInt(params[9]);
     fAccel  := StrToInt(params[10]);
     fEnergy := StrToInt(params[11]);
end;

destructor TLvObjBonusGunChange.destroy;
begin
     inherited destroy;
end;

function TLvObjBonusGunChange.readWidth : integer;
begin
     result := inherited readWidth;
end;

function TLvObjBonusGunChange.readHeight : integer;
begin
     result := inherited readHeight;
end;

end.

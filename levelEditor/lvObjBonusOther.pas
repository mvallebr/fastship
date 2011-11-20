unit lvObjBonusOther;

interface

uses classes, windows, levelObject, lvObjAnimated;

type
    TLvObjBonusOther = class (TLvObjAnimated)
    private
    protected
    public
        function readHeight : integer; override;
        function readWidth : integer; override;
        constructor create(yPos: integer; params: TStringList);
        destructor destroy; override;
    end;

implementation

uses main, sysutils;

constructor TLvObjBonusOther.create(yPos: integer; params: TStringList);
begin
     inherited create(yPos, params);
     animation.loadFromDir(frmMain.AppDir+'images\bonus\'+params[2]);
     setScreenSideUsingInteger(StrToInt(params[3]));
end;

destructor TLvObjBonusOther.destroy;
begin
     inherited destroy;
end;

function TLvObjBonusOther.readWidth : integer;
begin
     result := inherited readWidth;
end;

function TLvObjBonusOther.readHeight : integer;
begin
     result := inherited readHeight;
end;

end.

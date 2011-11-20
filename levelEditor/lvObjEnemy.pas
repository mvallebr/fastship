unit lvObjEnemy;

interface

uses classes, Graphics, levelObject, lvObjAnimated;

type
    TLvObjEnemy = class (TLvObjAnimated)
    private
    protected
        fGunID: string;
        fModID:  string;
    public
        function readHeight : integer; override;
        function readWidth : integer; override;
        constructor create(yPos: integer; params: TStringList);
        destructor destroy; override;
        property GunID: string read fGunID write fGunID;
        property ModID: string read fModID write fModID;
    end;

implementation


uses main, sysutils, dialogs;

constructor TLvObjEnemy.create(yPos: integer; params: TStringList);
begin
     inherited create(ypos, params);
     animation.loadFromDir(frmMain.AppDir+'images\enemy\'+params[2]);
     setScreenSideUsingInteger(StrToInt(params[3]));
     fGunID := params[11];
     fModID := params[12];
     colorLine := clRed;
end;

destructor TLvObjEnemy.destroy;
begin
     inherited destroy;
end;


function TLvObjEnemy.readWidth : integer;
begin
     if Animation=nil then begin
        result := 0;
        exit;
     end;
     result := Animation.readWidth;
end;

function TLvObjEnemy.readHeight : integer;
begin
     if Animation=nil then begin
        result := 0;
        exit;
     end;
     result := Animation.readHeight;
end;

end.

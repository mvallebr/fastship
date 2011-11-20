unit lvObjConstruction;

interface

uses classes, graphics, levelObject, lvObjAnimated;

type
    TLvObjConstruction = class (TLvObjAnimated)
    private
    protected

    public
        constructor create(yPos: integer; params: TStringList);
        destructor destroy; override;
    end;

implementation

uses main, sysutils, dialogs;

constructor TLvObjConstruction.create(yPos: integer; params: TStringList);
begin
     inherited create(yPos, params);
     fScreenSide := ssTop;
     animation.loadFromDir(frmMain.AppDir+'images\construction\'+params[2]);
     setScreenSideUsingInteger(StrToInt(params[3]));
     fEnergy := StrToInt(params[7]);
     fColision := (StrToInt(params[8])<>0);
     colorLine := clBlue;
end;

destructor TLvObjConstruction.destroy;
begin
     inherited destroy;
end;



end.

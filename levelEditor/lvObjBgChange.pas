unit lvObjBgChange;

interface

uses classes, windows, levelObject;

type
    TLvObjBgChange = class (TLevelObject)
    private
    protected
    public
        function readHeight : integer; override;
        function readWidth : integer; override;
        constructor create(yPos: integer; params: TStringList);
        destructor destroy; override;
    end;

implementation

uses main, sysutils, dialogs;

constructor TLvObjBgChange.create(yPos: integer; params: TStringList);
begin
     inherited create(yPos, params);
     animation.loadFromDir(frmMain.AppDir+'images\other');
end;

destructor TLvObjBgChange.destroy;
begin
     inherited destroy;
end;

function TLvObjBgChange.readWidth : integer;
begin
     result := inherited readWidth;
end;

function TLvObjBgChange.readHeight : integer;
begin
     result := inherited readHeight;
end;

end.

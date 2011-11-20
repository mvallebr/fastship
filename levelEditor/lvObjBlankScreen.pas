unit lvObjBlankScreen;

interface

uses classes, windows, levelObject;

type
    TLvObjBlankScreen = class (TLevelObject)
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

constructor TLvObjBlankScreen.create(yPos: integer; params: TStringList);
begin
     inherited create(yPos, params);
     animation.loadFromDir(frmMain.AppDir+'images\other');
end;

destructor TLvObjBlankScreen.destroy;
begin
     inherited destroy;
end;

function TLvObjBlankScreen.readWidth : integer;
begin
     result := inherited readWidth;
end;

function TLvObjBlankScreen.readHeight : integer;
begin
     result := inherited readHeight;
end;

end.

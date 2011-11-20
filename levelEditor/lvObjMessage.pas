unit lvObjMessage;


interface

uses classes, windows, levelObject;

type
    TLvObjMessage = class (TLevelObject)
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

constructor TLvObjMessage.create(yPos: integer; params: TStringList);
begin
     inherited create(yPos, params);
     animation.loadFromDir(frmMain.AppDir+'images\other');
end;

destructor TLvObjMessage.destroy;
begin
     inherited destroy;
end;

function TLvObjMessage.readWidth : integer;
begin
     result := inherited readWidth;
end;

function TLvObjMessage.readHeight : integer;
begin
     result := inherited readHeight;
end;

end.

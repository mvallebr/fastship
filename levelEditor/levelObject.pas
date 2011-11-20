unit levelObject;

interface

uses classes, windows, animation, graphics;

type
    TLevelObject = class (TObject)

    private
    protected
        fWidth, fHeight: Integer;
        fAnim: TAnimation;
        fName: string;
        fPos : TPoint;
    public
        function readHeight : integer; virtual;
        function readWidth : integer; virtual;
        property Width: Integer read readWidth;
        property Height: Integer read readHeight;
        property animation : TAnimation read fAnim write fAnim;
        property name: string read fName write fName;
        property Pos : TPoint read fPos write fPos;
        constructor create(yPos: integer; params: TStringList);
        destructor destroy; override;
        procedure draw(destBmp: TBitmap); virtual;
    end;

    TScreenSide =(ssTop, ssLeft, ssBottom, ssRight);
implementation

uses main, sysutils, dialogs;

constructor TLevelObject.create(yPos: integer; params: TStringList);
begin
     inherited create;
     fWidth := 0;
     fHeight := 0;
     fAnim := TAnimation.create;
     fName := params.Strings[1];
     fPos.y := yPos;
end;

destructor TLevelObject.destroy;
begin
     if (fAnim<>nil) then fAnim.destroy;
     inherited destroy;
end;


function TLevelObject.readWidth : integer;
begin
     if (fAnim<>nil) then result := fAnim.readWidth
     else result := fWidth;
end;

function TLevelObject.readHeight : integer;
begin
     if (fAnim<>nil) then result := fAnim.readHeight
     else result := fHeight;
end;

procedure TLevelObject.draw(destBmp: TBitmap);
var
   bitmap: TBitmap;
   xpos : integer;
begin
     if (fAnim=nil) or (width=0) or (height=0) then begin
        frmMain.memoLog.Lines.Add('Object "'+name+'" could not be rendered!'+
        ' width='+IntToStr(width) + ' height='+IntToStr(height)
           );
        beep;
        exit;
     end;
     frmMain.memoLog.Lines.Add('drawing obj x='+ IntToStr(fPos.x) + '%, y='+IntToStr(fPos.y));
     bitmap := fAnim.getCurrentPicture();
     {bitmap.TransparentMode := tmAuto;
     bitmap.Transparent := true;
     bitmap.TransparentColor := bitmap.Canvas.Pixels[0,0];}
     xpos := round(fPos.x * frmMain.Level.width/100);
     destBmp.canvas.CopyRect(
                     Rect(xpos, destBmp.height-fPos.y, xpos+width, destBmp.height-fPos.y+height),
                     bitmap.canvas,
                     Rect(0, 0, width, height));

     fAnim.advanceFrames(1);
end;

end.













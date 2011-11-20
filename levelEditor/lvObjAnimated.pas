unit lvObjAnimated;

interface

uses classes, graphics, levelObject;

type
    TLvObjAnimated = class (TLevelObject)
    private
    protected
        fVX, fVY: integer;
        fAccel:  integer;
        fScreenSide: TScreenSide;
        fDirX, fDirY: Integer;
        fEnergy: integer;
        fColision: boolean;
        colorLine : TColor;
        procedure setScreenSideUsingInteger(side: integer);
    public
        constructor create(yPos: integer; params: TStringList);
        destructor destroy; override;
        property VX: integer read fVX write fVX;
        property VY: integer read fVY write fVY;
        property Accel: integer read fAccel write fAccel;
        procedure draw(destBmp: TBitmap); override;
        property ScreenSide: TScreenSide read fScreenSide write fScreenSide;
        property DirX : Integer read fDirX write fDirX;
        property DirY : Integer read fDirY write fDirY;
        property Energy : Integer read fEnergy write fEnergy;
        property Colision : boolean read fColision write fColision;
    end;

implementation

uses main, sysUtils;

constructor TLvObjAnimated.create(yPos: integer; params: TStringList);
begin
     inherited create(ypos, params);
     fPos.x  := StrToInt(params[4]);
     fDirX := StrToInt(params[5]);
     fDirY := StrToInt(params[6]);
     if params.count>7 then fVX     := StrToInt(params[7]);
     if params.count>8 then fVY     := StrToInt(params[8]);
     if params.count>9 then fAccel  := StrToInt(params[9]);
     if params.count>10 then fEnergy := StrToInt(params[10]);
     colorLine := clBlack;
end;

destructor TLvObjAnimated.destroy;
begin
     inherited destroy;
end;


procedure TLvObjAnimated.setScreenSideUsingInteger(side: integer);
begin
     case side of
          0: fScreenSide := ssTop;
          1: fScreenSide := ssLeft;
          2: fScreenSide := ssBottom;
          3: fScreenSide := ssRight;
     end;
end;


procedure TLvObjAnimated.draw(destBmp: TBitmap);
var
   xpos : integer;
   cx, cy: integer;
begin
     if (fAnim=nil) or (width=0) or (height=0) then begin
        exit;
     end;
     with destBmp.canvas.Brush do begin
          case ScreenSide of
               ssTop: Color := frmMain.pnlTop.Color;
               ssLeft: Color := frmMain.pnlLeft.Color;
               ssBottom: Color := frmMain.pnlBottom.Color;
               ssRight: Color := frmMain.pnlRight.Color;
          end;
     end;
     //Draws the bitmap
     inherited Draw (destBmp);

     //Draw screen side
     xpos := round(fPos.x * frmMain.Level.width/100);
     destBmp.canvas.FillRect(Rect(
         xpos + round(width/3),
         destBmp.height - fPos.y + round(Height/3),
         xpos + 2*round(width/3),
         destBmp.height - fPos.y + 2*round(Height/3)
         ));

     //Draws the direction line
     with destBmp.canvas.Pen do begin
          Style := psDashDot;
          Width := 3;
          Color := colorLine;
     end;
     //Calculates center of image
     cx := xpos+round(width/2);
     cy := destBmp.height-fPos.y+round(Height/2);
     with destBmp.canvas do begin
          MoveTo(Cx, Cy);
          LineTo(Cx+10*dirX, CY+10*dirY);
          //Brush.Color := colorLine;
          TextOut(Cx, destBmp.height-fPos.y+Height, name);
     end;

end;




end.

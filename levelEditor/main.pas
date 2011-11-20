unit main;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  Menus, Grids, ExtCtrls, ToolWin, ComCtrls, Level, StdCtrls, FileCtrl;

type
  TfrmMain = class(TForm)
    Panel1: TPanel;
    StringGrid1: TStringGrid;
    MainMenu1: TMainMenu;
    File1: TMenuItem;
    Open1: TMenuItem;
    Save1: TMenuItem;
    N1: TMenuItem;
    Exit1: TMenuItem;
    openDialog: TOpenDialog;
    saveDialog: TSaveDialog;
    Panel2: TPanel;
    scrollBox: TScrollBox;
    ToolBar1: TToolBar;
    ToolButton1: TToolButton;
    ToolButton2: TToolButton;
    imgLevel: TImage;
    memoLog: TMemo;
    Splitter1: TSplitter;
    ImageListMenu: TImageList;
    Panel3: TPanel;
    cboLevelItem: TComboBox;
    Splitter2: TSplitter;
    pnlTop: TPanel;
    pnlBottom: TPanel;
    pnlRight: TPanel;
    pnlLeft: TPanel;
    procedure Exit1Click(Sender: TObject);
    procedure Open1Click(Sender: TObject);
    procedure Save1Click(Sender: TObject);
    procedure FormCreate(Sender: TObject);
    procedure FormDestroy(Sender: TObject);
    procedure ToolButton1Click(Sender: TObject);
    procedure ToolButton2Click(Sender: TObject);
    procedure Panel3Resize(Sender: TObject);
    procedure FormKeyDown(Sender: TObject; var Key: Word;
      Shift: TShiftState);
  private
    { Private declarations }
    fLevel: TLevel;
    fAppdir: string;
  public
    { Public declarations }
    property AppDir : string read fAppDir;
    property Level : TLevel read fLevel write fLevel;
    procedure paintLevel;
  end;

var
  frmMain: TfrmMain;

implementation

uses animation, levelObject;
{$R *.DFM}

procedure TfrmMain.Exit1Click(Sender: TObject);
begin
     Self.Close;
end;

procedure TfrmMain.Open1Click(Sender: TObject);
begin
     if (not openDialog.Execute) then exit;
     if (level<>nil) then level.destroy;
     try
        //Create level
        level := TLevel.create;
        //Load file
        level.loadFromFile(openDialog.filename);
        //Use loaded properties in visual components
        memoLog.Lines.add('level width = '+IntToStr(level.width));
        memoLog.Lines.add('level height = '+IntToStr(level.height));
        imgLevel.Width := level.Width;
        imgLevel.Height := level.Height;
        paintlevel;
     except
          on E: Exception do begin
             if (level<>nil) then begin
                level.destroy;
                level := nil;
             end;
             showmessage ('Exception on loading file: ' + E.message);
          end;
     end;
end;

procedure TfrmMain.Save1Click(Sender: TObject);
begin
     if (openDialog.Execute) then begin
        showmessage(openDialog.FileName);
     end;
end;

procedure TfrmMain.FormCreate(Sender: TObject);
begin
     level := nil;
     fAppDir := extractfilepath( ParamStr(0)); // get app dir
     fAppDir [length(appdir)]:= ' ';  //takes the last slash out
     fAppDir := extractfilepath( fAppDir); //get parent directory
//     showmessage (fAppDir);
end;

procedure TfrmMain.FormDestroy(Sender: TObject);
begin
     if (level <> nil) then level.destroy;
end;

procedure TfrmMain.paintLevel;
var
   anim: TAnimation;
   bitmap: TBitmap;
   x, y: integer;
   levelObject: TLevelObject;
   i: integer;
begin
     if (level = nil) then exit;
     // tile background on image
     anim := level.defaultGround;
     imgLevel.align := alNone;
     imgLevel.Stretch := false;
     imgLevel.picture.bitmap.Width := level.Width;
     imgLevel.picture.bitmap.Height := level.Height;
     bitmap := anim.getCurrentPicture();
     bitmap.Assign(anim.getCurrentPicture());
     imgLevel.picture.bitmap.PixelFormat := bitmap.PixelFormat;
     x := 0;
     y := 0;
     while x < level.width do begin
        while y < level.height do begin
           imgLevel.picture.bitmap.Canvas.CopyRect(
             Rect(x, y, x+bitmap.Width, y+bitmap.Height),
             bitmap.Canvas,
             Rect(0, 0, bitmap.Width, bitmap.Height)
          );
          y := y + bitmap.height;
        end;
        x := x + bitmap.width;
     end;
     //Now draw items
     for i := 0 to level.Items.Count-1 do begin
         levelObject := TLevelObject(level.Items.Objects[i]);
         levelObject.draw(imgLevel.picture.bitmap);
     end;
end;


procedure TfrmMain.ToolButton1Click(Sender: TObject);
begin
     Open1Click(Sender);
end;

procedure TfrmMain.ToolButton2Click(Sender: TObject);
begin
     Save1Click(Sender);
end;

procedure TfrmMain.Panel3Resize(Sender: TObject);
begin
     cboLevelItem.Width  := TPanel(Sender).width;
     cboLevelItem.Height := TPanel(Sender).Height;
end;

procedure TfrmMain.FormKeyDown(Sender: TObject; var Key: Word;
  Shift: TShiftState);
begin
     if key =  VK_DOWN then begin
        scrollbox.VertScrollBar.Position := scrollbox.VertScrollBar.Position + scrollbox.VertScrollBar.Increment;
     end else if key =  VK_UP then begin
        scrollbox.VertScrollBar.Position := scrollbox.VertScrollBar.Position - scrollbox.VertScrollBar.Increment;
     end else if key =  VK_RIGHT then begin
        scrollbox.HorzScrollBar.Position := scrollbox.HorzScrollBar.Position + scrollbox.HorzScrollBar.Increment;
     end else if key =  VK_LEFT then begin
        scrollbox.HorzScrollBar.Position := scrollbox.HorzScrollBar.Position - scrollbox.HorzScrollBar.Increment;
     end else if key =  VK_NEXT then begin
        scrollbox.VertScrollBar.Position := scrollbox.VertScrollBar.Position + scrollbox.Height - scrollbox.VertScrollBar.Increment;
     end else if key =  VK_PRIOR then begin
        scrollbox.VertScrollBar.Position := scrollbox.VertScrollBar.Position - scrollbox.Height + scrollbox.VertScrollBar.Increment;
     end;
end;

end.

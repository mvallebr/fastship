unit Animation;

interface

uses classes, graphics;

type
    TAnimation = class (TObject)

    private
        fitems : TStringList;
        fCurrentFrame: integer;
        procedure clearItems;
    public
        function readWidth : integer;
        function readHeight : integer;
        function readSize : integer;
        procedure setCurrentFrame(numFrame: integer);
        function getCurrentFrame: integer;
        property Width: Integer read readWidth;
        property Height: Integer read readHeight;
        property Items : TStringList read fitems;
        property Size : integer read readSize;
        property CurrentFrame: integer read getCurrentFrame write setCurrentFrame;
        constructor create;
        destructor destroy; override;
        procedure loadFromDir (dirname: string);
        procedure advanceFrames(numFrames: integer);
        function getCurrentPicture: TBitmap;
    end;

implementation

uses main, sysutils, dialogs, pngimage;

constructor TAnimation.create;
begin
     inherited create;
     fitems := TStringList.create;
     fCurrentFrame := -1;
end;

destructor TAnimation.destroy;
begin
     clearItems;
     if (fitems<>nil) then fitems.Destroy;
     inherited destroy;
end;

function TAnimation.readWidth : integer;
var
   picture : TBitmap;
begin
     if (getCurrentFrame()<0) then begin
        Result:= 0;
        exit;
     end;
     picture := getCurrentPicture();
     if (picture<>nil) then begin
          Result := picture.Width;
     end else begin
          result := 0;
     end;
end;

function TAnimation.readHeight : integer;
var
   picture : TBitmap;
begin
     if (getCurrentFrame()<0) then begin
        Result:= 0;
        exit;
     end;
     picture := getCurrentPicture();
     if (picture<>nil) then begin
          Result := picture.Height;
     end else begin
          result := 0;
     end;
end;

procedure TAnimation.loadFromDir (dirname: string);
var
   i: integer;
   SearchRec: TSearchRec;
   png: TPngObject;
   bitmap: TBitmap;
begin
     clearItems;
     if (dirname[length(dirname)]<>'\') then dirname := dirname + '\';
     i := findfirst(dirname + '*.png', faAnyFile, SearchRec);
     if i<>0 then
        raise Exception.Create ('Could not locate any file using pattern: "' +dirname + '*.png'+'"');
     png := nil;
     bitmap := nil;
     while (i=0) do begin
           try
              png := TPngObject.create;
              bitmap := TBitmap.create;
              png.LoadFromFile(dirname+SearchRec.Name);
              bitmap.Assign(png);
              png.destroy;
              fitems.AddObject(Searchrec.name, bitmap);
              //imgLevel.Picture.LoadFromFile(appdir+level.DefaultGround+'.png');
           except
                 on E: Exception do begin
                    if (png<>nil) then png.destroy;
                    if (bitmap<>nil) then bitmap.destroy;
                    ShowMessage('Exception occured when loading "'+dirname+SearchRec.Name+'":'+E.message );
                    raise E;
                 end;
           end;
           i := findNext(SearchRec);
     end;
     findclose(searchRec);
     fitems.Sort;
end;

procedure TAnimation.clearItems;
var
   I: integer;
   picture : TPngObject;
begin
     if (fitems=nil) then EXIT;
     for i := 0 to fitems.Count-1 do begin
         picture := TPngObject(fitems.Objects[i]);
         picture.destroy;
     end;
     fitems.clear;
end;

procedure TAnimation.setCurrentFrame(numFrame: integer);
begin
     if Size = 0 then begin
        fcurrentFrame := -1;
        exit;
     end;
     fCurrentFrame := numFrame;
     while fCurrentFrame >= Size do begin
           fCurrentFrame := fCurrentFrame - Size;
     end;
end;

function TAnimation.getCurrentFrame: integer;
begin
     if Size = 0 then begin
        fcurrentFrame := -1;
     end else if fcurrentFrame <0 then  begin
         fcurrentFrame := 0;
     end;
     Result := fcurrentFrame;
end;

procedure TAnimation.advanceFrames(numFrames: integer);
begin
     setCurrentFrame(fCurrentFrame+numFrames);
end;

function TAnimation.getCurrentPicture: TBitmap;
begin
     if (getCurrentFrame()<0) then begin
        result := nil;
        exit;
     end;
     result := TBitmap(fitems.Objects[getCurrentFrame()]);
end;

function TAnimation.readSize: integer;
begin
     result := fitems.count;
end;

end.













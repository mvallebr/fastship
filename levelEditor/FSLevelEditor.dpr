program FSLevelEditor;

uses
  Forms,
  main in 'main.pas' {frmMain},
  Level in 'Level.pas',
  animation in 'animation.pas',
  levelObject in 'levelObject.pas',
  lvObjMessage in 'lvObjMessage.pas',
  lvObjBlankScreen in 'lvObjBlankScreen.pas',
  lvObjBgChange in 'lvObjBgChange.pas',
  lvObjConstruction in 'lvObjConstruction.pas',
  lvObjEnemy in 'lvObjEnemy.pas',
  lvObjBonusGunChange in 'lvObjBonusGunChange.pas',
  lvObjBonusOther in 'lvObjBonusOther.pas',
  lvObjAnimated in 'lvObjAnimated.pas';

{$R *.RES}

begin
  Application.Initialize;
  Application.CreateForm(TfrmMain, frmMain);
  Application.Run;
end.

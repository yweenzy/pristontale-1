
//클랜만들기 처음 메세지
*szMsg1
Many warriors with same objectives\n
around the world gather and form a\n
group. It is called 'clan'. Clans \n
will guard and protect their own  \n
people. In order to form a clan,  \n
the clan must pay taxes to        \n
officially register. Do you wish  \n
to form a clan?                   \n

//클랜비용 메세지
*szMsg2
In order to form a clan,\n you need\n
to pay 500,000won. Do you wish to  \n
continue?

//클랜이름 넣으라는 메세지
*szMsg3
Type your clan name.

//클랜설명 메세지
*szMsg4
Once a clan is formed, players    \n
will be able to use their clan    \n
mark and phrases.                 \n
For more information, please visit\n
our website. After logging in, you\n
will be able to register/edit the \m
clan page, but you must be        \n
officially registered.            \n


//클랜결성조건 메세지
*szMsg5 
In order to officially register a \n
clan, you must meet these         \n
requirements.\n
(Requirements)\n
*Must have more than 6 members\n
 (including a clan chief)\n
*You have 10 days to recruit \n
 members\n
*Even if you officially registered,\n
 you must have minimum of 6 clan   \n
 members. Otherwise, the clan will \n
 automatically be canceled.        \n
 \n

//클랜신청 완료 메세지
*szClanMakeFinishMsg 
Also, clan members will be limited\n
to 15 persons. However, if the    \n
clan chief reaches level 40, he   \n
can recruit one more member for   \n
every 2 level increases. Up to 40 \n
members will be allowed in a clan.\n
Okay, all the registration has    \n
been finished. Now, you must start\n
recruiting clan members. If you   \n
have trouble, come back any time. \n

//클랜신청 자격미달 메세지(<---어따 쓰는 걸까요?) 지금은 사용안하고 있음
*szMsg254 
Do not even think about leading a\n
clan with your pity skills. Go   \n
back and take care of yourself   \n
first.

//클랜 해체 관련 메세지
*szMsg15 
Do you wish to disband the clan?


//클랜가입권유를 받는쪽에 메세지
*szJoin 
Clan Name : %s\n
Clan chief : %s\n
\n
You have been offered to join a   \n
clan from (clan name)             \n
Would you like to join?


//클랜 탈퇴 관련 메세지
*szSecession 
Clan Name: %s\n
Do you wish to leave the clan?


//npc를 만날때 클랜 구성원이 6명 이하로 떨어졌을때 메세지
*szMsg6 
In order to officially register a\n
clan, you must have minimum of 6 \n
clan members. You have %d days  \n
to recruit members.

*szMsg7
You must have minimum of 6   \n
members in order to          \n
officially register the clan.
You have %d hr. and %d min. left.



//클랜서버에 접속이 되지 않을때.
*szServerConnectErrorMsg
Unable to connect to server.     \n
Please try again later.     

//클랜마크 읽기 실패
*szReadClanMarkErrorMsg 
Failed to load clan mark from the \n
server.

//클랜만들기 취소 버턴을 클릭했을때
*szCancelMakeClan 
You don't wanna make \n
a clan? hm.. come again

//클랜서버쪽의 문제로 클랜 메뉴 에러
*szTranzationError 
DB error has occured. 
Menu will end now.


//클랜을 만들때 그 캐릭이 이미 다른 클랜에 가입되어 있을때(<-- 필요 없습니다.)
*szInsertClanWonError1 (삭제 했음)
 Already registered to   \n
another clan.

//클랜이름 중복
*szClanNameError 
This clan name already exists.  \n
Please try something else.

//클랜 서버에서 리턴코드를 100을 넘겨 줄때
*sz100Error 
Unknown error has occured.\n
Menu will end now.

//클랜서버에서 알수없는 리턴코드를 넘겨줄때
*szDefaultError 
Fatal error has occured on    \n
servers. \n
Menu will end now.

//클랜을 만들때 클랜장과 해당 클랜의 클랜명이 없을때 메세지(<-- 먼지 모르겠음)
*szReleseError (Deleted)
This character is not a clan chief nor \n
in any clan.

//클랜 탈퇴 성공
*szSecessionSuccess 
You have left the clan successfully.

//클랜을 탈퇴하면서 구성원이 6명이하로 떨어졌을 경우(<--- 이건 필요 없을듯)
*szSecession6DownMsg (Delete after confirm)
Your clan has been disbanded.

//탈퇴할려는 자가 클랜장일 경우.(<-- 클랜장은 탈퇴 못함)
*szSecessionChipMsg (Deleted)
This member is a clan chief.


//클랜원이 클랜을 탈퇴할때 클랜이름이 존재 하지 않거나..(<- 먼지 모르겠음)
*szSecession2ErrorMsg (Deleted)
Such clan does not exist. He might not be a    \n
clan chief or a clan member.




//가입권유를 받은 사람이 가이빈청을 받아 들임
*szClanJoinMsg 
Clan Name : %s\n
Clan chief : %s\n
Member : %s\n
\n
has joined the clan. 

//가입 할려는 유저가 다른 클랜에 가입 해 있을 경우(<--- 필요 없음)
*szClanJoinError2Msg (Deleted)
Already registered in another clan.


//일반 유저를 클랜에 가입 시킬려고 클랜짱의 이름이 빠져 있을때
*szClanJoinError3Msg (Deleted)
Such clan does not exist or not a clan chief.

//더 이상 클랜원을 추가 할수 없을때(가입 인원이 유동적으로 변할 수 있게 바꿔 주세요)
//(다른곳에서 제어하고 있음) 이 메세지 삭제 했음
*szClanJoinError4Msg 
Clan member is limited to 15 persons.


//클랜장이 일반 유저한테 가입원유를 했는데 가입 받은자가  거부를 할 경우
*szClanJoinCancelMsg 
%s has refused to join the clan.


//클랜을 가입 권유를 하여 클랜에 가입을 성공했을때 메세지
*szClanJoinsucesssMsg 
%s     \n
has successfully joined the clan. 




//클랜에서 클랜원을 추방 성공
*szReMoveClanWonMsg has
been expelled from the clan.

//클랜원을 추방하고나서 마지막 메세지(<- 머지 모르겠음)
(추방 단계에서 자기가 추방한 클랜원들 리스트 보여줄때 사용함)
*szReMoveHeaderMsg
Here is a list of expelled members.

//클랜 해체 관련 메세지
*szReConfReleaseMsg 

If you disband the clan, all      \n
information about the clan and    \n
clan members will be destroyed.   \n
Do you wish to continue anyways?  \n


//클랜이 등록되지 않은 상태에서 클랜을 해체할 때
*szNoRecordReleaseMsg 
You sure you want to disband?    \n

//클랜해체 종료
*szFinishReleaseMsg 
Clan has been successfully disbanded... 

//클랜 탈퇴할때 재 메세지
*szSecessionMsg 
Are you sure you want to leave the  \n
clan? 

//클랜탈퇴 종료 메세지(<--- 이건 멀까요?)
 (탈퇴후 마지막에 보여주는 메세지)
*szFinishSecessionMsg
Clan Name: %s\n
Member : %s\n
has left the clan.


//클랜을 만들려고 할때 계정에 클랜 장이 있을 경우(<-- 이것도 필요 없을 듯)
(계정에 클랜장이 있는데 또 만들려고 할때 보여줌)
*szisCheckClanJangErrorMsg
You already have a clan chief        \n
character on this account. There can \n
only 1 clan chief each server.


//클랜만들때 클랜 비용이 부족할때
*szMoneyErrorMsg 
You must pay 500,000 won in order to \n
form a clan. 


//클랜 만들려고 할때 능력치 부족(<-- 이것도 필요 없을 듯)
(능력치지가 미달되면 클랜을 못만드는걸로 알고 있음 그에 관련된 메세지)
*szAbilityErrorMsg
You do not have enough    \n
stat points to form a clan.


//클랜원 추방 할 때 메세지
*szRemoveShortClanWonMsg 
Your clan will not have     \n
enough members if you expel \n
this character. Do you still\n
wish to continue?


//클랜원 추방 후 결과 메세지
*szRemoveShowrtClanWonResultMsg 
Clan members are less than \n
6 persons. Please recruit  \n
more members.



//클랜 이름 입력 메세지(<-- 반복?)
*szNoName 
Please enter the clan name.

//로딩 메세지
*szLoading 
Connecting to server.


*========케릭터 삭제할때 나오는 메세지임 상의가 필요함=======================

/////////캐릭터 삭제 메세지(<-- 필요 없을 듯)
*szDeleteChaReleaseBefore 
The character you are about to delete\n
is a clan chief. If you delete this  \n
character, the clan will be deleted  \n
as well. Do you wish to continue?

(<-- 역시 필요 없을 듯)
*szDeleteChaReleaseFinish
Clan has been deleted.


(<-- 필요 없음)
*szDeleteChaSecessionBefore
The character you are about to  \n
delete is currently in a clan.  \n
It will be automatically banned \n
from the clan if deleted. Do you\n
wish to continue?

//캐릭터 삭제 하면서 클랜에서 탈퇴(<- 필요 없음)
*szDeleteChaSecessionFinish 
You have left the clan successfully.

//클랜 삭제 실패(<- 이건 머죠?)
*szDeleteChaError 
You have failed to delete the    \n
clan. Your character cannot be   \n
deleted.

========================================================

//클랜이 등록이 될때
*szMakeFinishClan 
Congratulations!\n
[%s]clan\n
is now officially registered.

//클랜원이 6명 미만일때
*szClanWon6Down 
Your clan members became less  \n
than 6 persons. Please recruit \n
more members to avoid          \n
disbandment.


//클랜이 신청 중일때(<-- 필요 없을 듯)
*szClanUserNoMakeMsg 
Name of Clan : %s\n
Clan registering is in process.
Please be patient.

//클랜이 등록될때(반복)
*szMakeFinishClanWon 
Name of Clan : %s\n
The clan has been officially registered.

//서버에 접속이 되지않을때
*ClanServerInspect 
Server maintenance.

//해체된 클랜원들이 npc를 만날때
*szClanUserRelease 
That clan no longer exists.

//서버에 이상이 있을때
*Replay
Please try again.

//클랜 만들기 마지막 메세지(필요 없을듯)
(클랜만드는 단계에서 서버에 등록할때 중간에 로드 화면상에 들어가는 메세지임)
*szClanMakedowninfo
Registering clan.

//자동해체, 클랜장이 클랜이 미등록된 상태에서 해체하였을 경우
*szClanUserReleaseMsg 
Name of Clan: %s\n
Clan registering has been cancelled.

//추방 결과 메세지(<-- 반복 )
*szClanUserRemove
Name of Clan: %s\n
Member: %s\n
You have been expelled. 

//클랜원 이 만땅일때
*szClanWonOver
You cannot recruit anymore members.

*szError_Msg
Unknown error has occured.

*szNoLevel
A person who is below level\n
50 cannot form a clan.

*szRemoveSecond
Do you wish to disband this person?

*szRemoveSecondResult
Disbanded successfully.

*szLeaveClanConfirm
Wanna entrust a clan chief?
You must pay 300,000 gold to entrust\n
a clan chief. But, that person must \n
be equal or higher level than you.  \n
Once it's been entrusted, you will  \n
become a normal clan member. Please \n
consider it carefully.

*szLeaveClanNoMoney
To entrust a clan chief, you \n
must pay 300,000 gold.

*szLeaveClanSuccess
Clan chief has been changed to (%s)\n



*szLeaveClanNoLevel
Level not high enough to \n
become a clan chief.


*szLeaveClanReConfirm
Entrust a clan chief to (%s)?\n

*szNoLeaveClan
Cannot entrust a clan chief.  \n
Must register the clan first.

*szLeaveClanMessage
Clan chief has been changed from(%s)
to (%s).

*szLeaveClanDownLevel
Level lower than clan chief.    \n
Unable to entrust.

*szSubChipAppoint
Do you wish to appoint\n
(%s) as a vice chief?

*szSubChipAppointEnd
Appointed as a vice chief.

*szSubChipRelease
Do you wish to discharge\n
(%s) from vice chief?

*szSubChipReleseEnd
(%s) has been discharged\n
from vice chief.

*szClanIs4DayCheckMsg
(%s)\n
can't clan members in 4days after the clan dismiss.\n














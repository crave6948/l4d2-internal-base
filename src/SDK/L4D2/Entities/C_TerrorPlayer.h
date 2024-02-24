#pragma once

#include "C_CSPlayer.h"

class C_TerrorPlayer : public C_CSPlayer
{
public:
	virtual							~C_TerrorPlayer() = 0;

	virtual void					OnSpawn(void) = 0;
	virtual bool					IsReadyToShove(void) = 0;
	virtual void					SetNextShoveTime(float unk1) = 0;
	virtual bool					CanPlayerJump(void) const = 0;
	virtual bool					CanBeShoved(void) = 0;
	virtual float					GetCrawlTopSpeed(void) const = 0;
	virtual void					OnWeaponFired(void) = 0;
	virtual bool					ShouldShowVOIPIcon(void) const = 0;
	virtual bool					CanUseFlashlight(void) const = 0;
	virtual void					CalcViewModifications(Vector& unk1, Vector& unk2) = 0;

public:
	M_NETVAR(m_shoveForce, Vector, "CTerrorPlayer", "m_shoveForce");
	M_NETVAR(m_airMovementRestricted, int, "CTerrorPlayer", "m_airMovementRestricted");
	M_NETVAR(m_stunTimer, void*, "CTerrorPlayer", "m_stunTimer");
	M_NETVAR(m_duration, float, "CTerrorPlayer", "m_duration");
	M_NETVAR(m_timestamp, float, "CTerrorPlayer", "m_timestamp");
	M_NETVAR(m_isInMissionStartArea, bool, "CTerrorPlayer", "m_isInMissionStartArea");
	M_NETVAR(m_isCulling, bool, "CTerrorPlayer", "m_isCulling");
	M_NETVAR(m_isRelocating, bool, "CTerrorPlayer", "m_isRelocating");
	M_NETVAR(m_pushEntity, EHANDLE, "CTerrorPlayer", "m_pushEntity");
	M_NETVAR(m_pushDistance, float, "CTerrorPlayer", "m_pushDistance");
	M_NETVAR(m_ghostSpawnState, int, "CTerrorPlayer", "m_ghostSpawnState");
	M_NETVAR(m_ghostSpawnClockMaxDelay, int, "CTerrorPlayer", "m_ghostSpawnClockMaxDelay");
	M_NETVAR(m_ghostSpawnClockCurrentDelay, int, "CTerrorPlayer", "m_ghostSpawnClockCurrentDelay");
	M_NETVAR(m_flNextShoveTime, float, "CTerrorPlayer", "m_flNextShoveTime");
	M_NETVAR(m_iShovePenalty, int, "CTerrorPlayer", "m_iShovePenalty");
	M_NETVAR(m_dragTarget, EHANDLE, "CTerrorPlayer", "m_dragTarget");
	M_NETVAR(m_lineOfScrimmagePos, Vector, "CTerrorPlayer", "m_lineOfScrimmagePos");
	M_NETVAR(m_lineOfScrimmageAngle, Vector, "CTerrorPlayer", "m_lineOfScrimmageAngle");
	M_NETVAR(m_rearLineOfScrimmagePos, Vector, "CTerrorPlayer", "m_rearLineOfScrimmagePos");
	M_NETVAR(m_rearLineOfScrimmageAngle, Vector, "CTerrorPlayer", "m_rearLineOfScrimmageAngle");
	M_NETVAR(m_scrimmageSphereCenter, Vector, "CTerrorPlayer", "m_scrimmageSphereCenter");
	M_NETVAR(m_scrimmageSphereInitialRadius, float, "CTerrorPlayer", "m_scrimmageSphereInitialRadius");
	M_NETVAR(m_scrimmageStartTime, float, "CTerrorPlayer", "m_scrimmageStartTime");
	M_NETVAR(m_survivorsLineOfScrimmageDistance, float, "CTerrorPlayer", "m_survivorsLineOfScrimmageDistance");
	M_NETVAR(m_isAutoCrouchEnabled, int, "CTerrorPlayer", "m_isAutoCrouchEnabled");
	M_NETVAR(m_autoCrouchTimer, void*, "CTerrorPlayer", "m_autoCrouchTimer");
	M_NETVAR(m_yardLineAngles, Vector, "CTerrorPlayer", "m_yardLineAngles[0]");
	M_NETVAR(m_yardLinePos, Vector, "CTerrorPlayer", "m_yardLinePos[0]");
	M_NETVAR(m_noAvoidanceTimer, void*, "CTerrorPlayer", "m_noAvoidanceTimer");
	M_NETVAR(m_TimeForceExternalView, float, "CTerrorPlayer", "m_TimeForceExternalView");
	M_NETVAR(m_nVariantType, int, "CTerrorPlayer", "m_nVariantType");
	M_NETVAR(m_mainSequenceStartTime, float, "CTerrorPlayer", "m_mainSequenceStartTime");
	M_NETVAR(m_grenadeLayerSequence, int, "CTerrorPlayer", "m_grenadeLayerSequence");
	M_NETVAR(m_fireLayerSequence, int, "CTerrorPlayer", "m_fireLayerSequence");
	M_NETVAR(m_flinchLayerSequence, int, "CTerrorPlayer", "m_flinchLayerSequence");
	M_NETVAR(m_fidgetLayerSequence, int, "CTerrorPlayer", "m_fidgetLayerSequence");
	M_NETVAR(m_reloadLayerSequence, int, "CTerrorPlayer", "m_reloadLayerSequence");
	M_NETVAR(m_reloadAltLayerSequence, int, "CTerrorPlayer", "m_reloadAltLayerSequence");
	M_NETVAR(m_reloadLayerNumShells, int, "CTerrorPlayer", "m_reloadLayerNumShells");
	M_NETVAR(m_grenadeLayerStartTime, float, "CTerrorPlayer", "m_grenadeLayerStartTime");
	M_NETVAR(m_fireLayerStartTime, float, "CTerrorPlayer", "m_fireLayerStartTime");
	M_NETVAR(m_flinchLayerStartTime, float, "CTerrorPlayer", "m_flinchLayerStartTime");
	M_NETVAR(m_fidgetLayerStartTime, float, "CTerrorPlayer", "m_fidgetLayerStartTime");
	M_NETVAR(m_reloadLayerStartTime, float, "CTerrorPlayer", "m_reloadLayerStartTime");
	M_NETVAR(m_reloadAltLayerStartTime, float, "CTerrorPlayer", "m_reloadAltLayerStartTime");
	M_NETVAR(m_hBuildableButtonUseEnt, EHANDLE, "CTerrorPlayer", "m_hBuildableButtonUseEnt");
	M_NETVAR(m_NetGestureSequence, void*, "CTerrorPlayer", "m_NetGestureSequence");
	M_NETVAR(m_NetGestureActivity, void*, "CTerrorPlayer", "m_NetGestureActivity");
	M_NETVAR(m_NetGestureStartTime, void*, "CTerrorPlayer", "m_NetGestureStartTime");
	M_NETVAR(m_fServerAnimStartTime, float, "CTerrorPlayer", "m_fServerAnimStartTime");
	M_NETVAR(m_hasVisibleThreats, bool, "CTerrorPlayer", "m_hasVisibleThreats");
	M_NETVAR(m_burnPercent, float, "CTerrorPlayer", "m_burnPercent");
	M_NETVAR(m_bbqPercent, float, "CTerrorPlayer", "m_bbqPercent");
	M_NETVAR(m_holdingObject, bool, "CTerrorPlayer", "m_holdingObject");
	M_NETVAR(m_healthBuffer, float, "CTerrorPlayer", "m_healthBuffer");
	M_NETVAR(m_healthBufferTime, float, "CTerrorPlayer", "m_healthBufferTime");
	M_NETVAR(m_isGoingToDie, bool, "CTerrorPlayer", "m_isGoingToDie");
	M_NETVAR(m_noiseLevel, float, "CTerrorPlayer", "m_noiseLevel");
	M_NETVAR(m_noiseLevelLatch, int, "CTerrorPlayer", "m_noiseLevelLatch");
	M_NETVAR(m_iBloodyHandsLevel, int, "CTerrorPlayer", "m_iBloodyHandsLevel");
	M_NETVAR(m_itTimer, void*, "CTerrorPlayer", "m_itTimer");
	M_NETVAR(m_bAdrenalineActive, bool, "CTerrorPlayer", "m_bAdrenalineActive");
	M_NETVAR(m_survivorCharacter, int, "CTerrorPlayer", "m_survivorCharacter");
	M_NETVAR(m_zombieClass, int, "CTerrorPlayer", "m_zombieClass");
	M_NETVAR(m_zombieState, int, "CTerrorPlayer", "m_zombieState");
	M_NETVAR(m_isIncapacitated, bool, "CTerrorPlayer", "m_isIncapacitated");
	M_NETVAR(m_isCalm, bool, "CTerrorPlayer", "m_isCalm");
	M_NETVAR(m_useActionOwner, EHANDLE, "CTerrorPlayer", "m_useActionOwner");
	M_NETVAR(m_useActionTarget, EHANDLE, "CTerrorPlayer", "m_useActionTarget");
	M_NETVAR(m_iCurrentUseAction, int, "CTerrorPlayer", "m_iCurrentUseAction");
	M_NETVAR(m_reviveOwner, EHANDLE, "CTerrorPlayer", "m_reviveOwner");
	M_NETVAR(m_reviveTarget, EHANDLE, "CTerrorPlayer", "m_reviveTarget");
	M_NETVAR(m_tongueVictim, EHANDLE, "CTerrorPlayer", "m_tongueVictim");
	M_NETVAR(m_tongueOwner, EHANDLE, "CTerrorPlayer", "m_tongueOwner");
	M_NETVAR(m_tongueVictimTimer, void*, "CTerrorPlayer", "m_tongueVictimTimer");
	M_NETVAR(m_initialTonguePullDir, Vector, "CTerrorPlayer", "m_initialTonguePullDir");
	M_NETVAR(m_isHangingFromTongue, bool, "CTerrorPlayer", "m_isHangingFromTongue");
	M_NETVAR(m_reachedTongueOwner, EHANDLE, "CTerrorPlayer", "m_reachedTongueOwner");
	M_NETVAR(m_isProneTongueDrag, int, "CTerrorPlayer", "m_isProneTongueDrag");
	M_NETVAR(m_positionEntity, int, "CTerrorPlayer", "m_positionEntity");
	M_NETVAR(m_customAbility, int, "CTerrorPlayer", "m_customAbility");
	M_NETVAR(m_checkpointAwardCounts, int, "CTerrorPlayer", "m_checkpointAwardCounts[0]");
	M_NETVAR(m_missionAwardCounts, int, "CTerrorPlayer", "m_missionAwardCounts[0]");
	M_NETVAR(m_checkpointZombieKills, int, "CTerrorPlayer", "m_checkpointZombieKills[0]");
	M_NETVAR(m_missionZombieKills, int, "CTerrorPlayer", "m_missionZombieKills[0]");
	M_NETVAR(m_checkpointSurvivorDamage, int, "CTerrorPlayer", "m_checkpointSurvivorDamage");
	M_NETVAR(m_missionSurvivorDamage, int, "CTerrorPlayer", "m_missionSurvivorDamage");
	M_NETVAR(m_classSpawnCount, int, "CTerrorPlayer", "m_classSpawnCount[0]");
	M_NETVAR(m_iMaxHealth, int, "CTerrorPlayer", "m_iMaxHealth");
	M_NETVAR(m_maxDeadDuration, float, "CTerrorPlayer", "m_maxDeadDuration");
	M_NETVAR(m_totalDeadDuration, float, "CTerrorPlayer", "m_totalDeadDuration");
	M_NETVAR(m_jumpSupressedUntil, float, "CTerrorPlayer", "m_jumpSupressedUntil");
	M_NETVAR(m_checkpointMedkitsUsed, int, "CTerrorPlayer", "m_checkpointMedkitsUsed");
	M_NETVAR(m_checkpointPillsUsed, int, "CTerrorPlayer", "m_checkpointPillsUsed");
	M_NETVAR(m_missionMedkitsUsed, int, "CTerrorPlayer", "m_missionMedkitsUsed");
	M_NETVAR(m_missionPillsUsed, int, "CTerrorPlayer", "m_missionPillsUsed");
	M_NETVAR(m_checkpointMolotovsUsed, int, "CTerrorPlayer", "m_checkpointMolotovsUsed");
	M_NETVAR(m_missionMolotovsUsed, int, "CTerrorPlayer", "m_missionMolotovsUsed");
	M_NETVAR(m_checkpointPipebombsUsed, int, "CTerrorPlayer", "m_checkpointPipebombsUsed");
	M_NETVAR(m_missionPipebombsUsed, int, "CTerrorPlayer", "m_missionPipebombsUsed");
	M_NETVAR(m_checkpointBoomerBilesUsed, int, "CTerrorPlayer", "m_checkpointBoomerBilesUsed");
	M_NETVAR(m_missionBoomerBilesUsed, int, "CTerrorPlayer", "m_missionBoomerBilesUsed");
	M_NETVAR(m_checkpointAdrenalinesUsed, int, "CTerrorPlayer", "m_checkpointAdrenalinesUsed");
	M_NETVAR(m_missionAdrenalinesUsed, int, "CTerrorPlayer", "m_missionAdrenalinesUsed");
	M_NETVAR(m_checkpointDefibrillatorsUsed, int, "CTerrorPlayer", "m_checkpointDefibrillatorsUsed");
	M_NETVAR(m_missionDefibrillatorsUsed, int, "CTerrorPlayer", "m_missionDefibrillatorsUsed");
	M_NETVAR(m_checkpointDamageTaken, int, "CTerrorPlayer", "m_checkpointDamageTaken");
	M_NETVAR(m_missionDamageTaken, int, "CTerrorPlayer", "m_missionDamageTaken");
	M_NETVAR(m_checkpointReviveOtherCount, int, "CTerrorPlayer", "m_checkpointReviveOtherCount");
	M_NETVAR(m_missionReviveOtherCount, int, "CTerrorPlayer", "m_missionReviveOtherCount");
	M_NETVAR(m_checkpointFirstAidShared, int, "CTerrorPlayer", "m_checkpointFirstAidShared");
	M_NETVAR(m_missionFirstAidShared, int, "CTerrorPlayer", "m_missionFirstAidShared");
	M_NETVAR(m_checkpointIncaps, int, "CTerrorPlayer", "m_checkpointIncaps");
	M_NETVAR(m_missionIncaps, int, "CTerrorPlayer", "m_missionIncaps");
	M_NETVAR(m_checkpointDamageToTank, int, "CTerrorPlayer", "m_checkpointDamageToTank");
	M_NETVAR(m_checkpointDamageToWitch, int, "CTerrorPlayer", "m_checkpointDamageToWitch");
	M_NETVAR(m_missionAccuracy, int, "CTerrorPlayer", "m_missionAccuracy");
	M_NETVAR(m_checkpointHeadshots, int, "CTerrorPlayer", "m_checkpointHeadshots");
	M_NETVAR(m_checkpointHeadshotAccuracy, int, "CTerrorPlayer", "m_checkpointHeadshotAccuracy");
	M_NETVAR(m_missionHeadshotAccuracy, int, "CTerrorPlayer", "m_missionHeadshotAccuracy");
	M_NETVAR(m_checkpointDeaths, int, "CTerrorPlayer", "m_checkpointDeaths");
	M_NETVAR(m_missionDeaths, int, "CTerrorPlayer", "m_missionDeaths");
	M_NETVAR(m_checkpointMeleeKills, int, "CTerrorPlayer", "m_checkpointMeleeKills");
	M_NETVAR(m_missionMeleeKills, int, "CTerrorPlayer", "m_missionMeleeKills");
	M_NETVAR(m_checkpointPZIncaps, int, "CTerrorPlayer", "m_checkpointPZIncaps");
	M_NETVAR(m_checkpointPZTankDamage, int, "CTerrorPlayer", "m_checkpointPZTankDamage");
	M_NETVAR(m_checkpointPZHunterDamage, int, "CTerrorPlayer", "m_checkpointPZHunterDamage");
	M_NETVAR(m_checkpointPZSmokerDamage, int, "CTerrorPlayer", "m_checkpointPZSmokerDamage");
	M_NETVAR(m_checkpointPZBoomerDamage, int, "CTerrorPlayer", "m_checkpointPZBoomerDamage");
	M_NETVAR(m_checkpointPZJockeyDamage, int, "CTerrorPlayer", "m_checkpointPZJockeyDamage");
	M_NETVAR(m_checkpointPZSpitterDamage, int, "CTerrorPlayer", "m_checkpointPZSpitterDamage");
	M_NETVAR(m_checkpointPZChargerDamage, int, "CTerrorPlayer", "m_checkpointPZChargerDamage");
	M_NETVAR(m_checkpointPZKills, int, "CTerrorPlayer", "m_checkpointPZKills");
	M_NETVAR(m_checkpointPZPounces, int, "CTerrorPlayer", "m_checkpointPZPounces");
	M_NETVAR(m_checkpointPZPushes, int, "CTerrorPlayer", "m_checkpointPZPushes");
	M_NETVAR(m_checkpointPZTankPunches, int, "CTerrorPlayer", "m_checkpointPZTankPunches");
	M_NETVAR(m_checkpointPZTankThrows, int, "CTerrorPlayer", "m_checkpointPZTankThrows");
	M_NETVAR(m_checkpointPZHung, int, "CTerrorPlayer", "m_checkpointPZHung");
	M_NETVAR(m_checkpointPZPulled, int, "CTerrorPlayer", "m_checkpointPZPulled");
	M_NETVAR(m_checkpointPZBombed, int, "CTerrorPlayer", "m_checkpointPZBombed");
	M_NETVAR(m_checkpointPZVomited, int, "CTerrorPlayer", "m_checkpointPZVomited");
	M_NETVAR(m_checkpointPZHighestDmgPounce, int, "CTerrorPlayer", "m_checkpointPZHighestDmgPounce");
	M_NETVAR(m_checkpointPZLongestSmokerGrab, int, "CTerrorPlayer", "m_checkpointPZLongestSmokerGrab");
	M_NETVAR(m_checkpointPZLongestJockeyRide, int, "CTerrorPlayer", "m_checkpointPZLongestJockeyRide");
	M_NETVAR(m_checkpointPZNumChargeVictims, int, "CTerrorPlayer", "m_checkpointPZNumChargeVictims");
	M_NETVAR(m_isHangingFromLedge, bool, "CTerrorPlayer", "m_isHangingFromLedge");
	M_NETVAR(m_isFallingFromLedge, bool, "CTerrorPlayer", "m_isFallingFromLedge");
	M_NETVAR(m_hangTimer, void*, "CTerrorPlayer", "m_hangTimer");
	M_NETVAR(m_hangAirPos, Vector, "CTerrorPlayer", "m_hangAirPos");
	M_NETVAR(m_hangPos, Vector, "CTerrorPlayer", "m_hangPos");
	M_NETVAR(m_hangStandPos, Vector, "CTerrorPlayer", "m_hangStandPos");
	M_NETVAR(m_hangNormal, Vector, "CTerrorPlayer", "m_hangNormal");
	M_NETVAR(m_frustration, int, "CTerrorPlayer", "m_frustration");
	M_NETVAR(m_clientIntensity, int, "CTerrorPlayer", "m_clientIntensity");
	M_NETVAR(m_pummelVictim, EHANDLE, "CTerrorPlayer", "m_pummelVictim");
	M_NETVAR(m_pummelAttacker, EHANDLE, "CTerrorPlayer", "m_pummelAttacker");
	M_NETVAR(m_queuedPummelVictim, EHANDLE, "CTerrorPlayer", "m_queuedPummelVictim");
	M_NETVAR(m_carryAttacker, EHANDLE, "CTerrorPlayer", "m_carryAttacker");
	M_NETVAR(m_carryVictim, EHANDLE, "CTerrorPlayer", "m_carryVictim");
	M_NETVAR(m_pounceVictim, EHANDLE, "CTerrorPlayer", "m_pounceVictim");
	M_NETVAR(m_pounceAttacker, EHANDLE, "CTerrorPlayer", "m_pounceAttacker");
	M_NETVAR(m_jockeyVictim, EHANDLE, "CTerrorPlayer", "m_jockeyVictim");
	M_NETVAR(m_jockeyAttacker, EHANDLE, "CTerrorPlayer", "m_jockeyAttacker");
	M_NETVAR(m_jockeyDesiredMove, Vector, "CTerrorPlayer", "m_jockeyDesiredMove");
	M_NETVAR(m_jockeyFirmAttach, int, "CTerrorPlayer", "m_jockeyFirmAttach");
	M_NETVAR(m_jockeyRotatedDesire, int, "CTerrorPlayer", "m_jockeyRotatedDesire");
	M_NETVAR(m_knockdownReason, int, "CTerrorPlayer", "m_knockdownReason");
	M_NETVAR(m_knockdownTimer, void*, "CTerrorPlayer", "m_knockdownTimer");
	M_NETVAR(m_staggerTimer, void*, "CTerrorPlayer", "m_staggerTimer");
	M_NETVAR(m_staggerStart, Vector, "CTerrorPlayer", "m_staggerStart");
	M_NETVAR(m_staggerDir, Vector, "CTerrorPlayer", "m_staggerDir");
	M_NETVAR(m_staggerDist, float, "CTerrorPlayer", "m_staggerDist");
	M_NETVAR(m_tugTimer, void*, "CTerrorPlayer", "m_tugTimer");
	M_NETVAR(m_tugStart, Vector, "CTerrorPlayer", "m_tugStart");
	M_NETVAR(m_tugDir, Vector, "CTerrorPlayer", "m_tugDir");
	M_NETVAR(m_tugDist, float, "CTerrorPlayer", "m_tugDist");
	M_NETVAR(m_currentReviveCount, int, "CTerrorPlayer", "m_currentReviveCount");
	M_NETVAR(m_bIsOnThirdStrike, bool, "CTerrorPlayer", "m_bIsOnThirdStrike");
	M_NETVAR(m_bIsFirstManOut, bool, "CTerrorPlayer", "m_bIsFirstManOut");
	M_NETVAR(m_music, void*, "CTerrorPlayer", "m_music");
	M_NETVAR(nv_m_CIDamageDuck, float, "CTerrorPlayer", "nv_m_CIDamageDuck");
	M_NETVAR(nv_m_CIDamageMob, float, "CTerrorPlayer", "nv_m_CIDamageMob");
	M_NETVAR(nv_m_zombatMusic, float, "CTerrorPlayer", "nv_m_zombatMusic");
	M_NETVAR(nv_m_zombatMusic3, float, "CTerrorPlayer", "nv_m_zombatMusic3");
	M_NETVAR(nv_m_inCheckpoint, int, "CTerrorPlayer", "nv_m_inCheckpoint");
	M_NETVAR(nv_m_ambientVolume, float, "CTerrorPlayer", "nv_m_ambientVolume");
	M_NETVAR(nv_m_witchRage, float, "CTerrorPlayer", "nv_m_witchRage");
	M_NETVAR(m_fNVAdrenaline, float, "CTerrorPlayer", "m_fNVAdrenaline");
	M_NETVAR(m_usingMountedGun, bool, "CTerrorPlayer", "m_usingMountedGun");
	M_NETVAR(m_usingMountedWeapon, bool, "CTerrorPlayer", "m_usingMountedWeapon");
	M_NETVAR(m_isGhost, bool, "CTerrorPlayer", "m_isGhost");
	M_NETVAR(m_bWasPresentAtSurvivalStart, bool, "CTerrorPlayer", "m_bWasPresentAtSurvivalStart");
	M_NETVAR(m_vocalizationSubject, int, "CTerrorPlayer", "m_vocalizationSubject");
	M_NETVAR(m_vocalizationSubjectTimer, void*, "CTerrorPlayer", "m_vocalizationSubjectTimer");
	M_NETVAR(m_pounceStartPosition, Vector, "CTerrorPlayer", "m_pounceStartPosition");
	M_NETVAR(m_isAttemptingToPounce, bool, "CTerrorPlayer", "m_isAttemptingToPounce");
	M_NETVAR(m_vomitStart, float, "CTerrorPlayer", "m_vomitStart");
	M_NETVAR(m_vomitFadeStart, float, "CTerrorPlayer", "m_vomitFadeStart");
	M_NETVAR(m_bashedStart, float, "CTerrorPlayer", "m_bashedStart");
	M_NETVAR(m_salivaStart, float, "CTerrorPlayer", "m_salivaStart");
	M_NETVAR(m_iVersusTeam, int, "CTerrorPlayer", "m_iVersusTeam");
	M_NETVAR(m_scrimmageType, int, "CTerrorPlayer", "m_scrimmageType");
	M_NETVAR(m_lookatPlayer, int, "CTerrorPlayer", "m_lookatPlayer");
	M_NETVAR(m_bSurvivorGlowEnabled, bool, "CTerrorPlayer", "m_bSurvivorGlowEnabled");
	M_NETVAR(m_bSurvivorPositionHidingWeapons, bool, "CTerrorPlayer", "m_bSurvivorPositionHidingWeapons");

public:
	inline bool CanAttackFull() {
		return (CanAttack() && (m_flNextAttack() <= I::GlobalVars->curtime));
	}
	inline bool CanAttackFull(float timeToFaster) {
		return (CanAttack() && ((m_flNextAttack() - timeToFaster) <= I::GlobalVars->curtime));
	}
	inline bool CanShoveFull() {
		return ((m_flNextShoveTime() <= I::GlobalVars->curtime));
	}
};

class C_SurvivorBot : public C_TerrorPlayer
{
public:
	virtual ~C_SurvivorBot() = 0;

public:
	M_NETVAR(m_humanSpectatorUserID, int, "SurvivorBot", "m_humanSpectatorUserID");
	M_NETVAR(m_humanSpectatorEntIndex, int, "SurvivorBot", "m_humanSpectatorEntIndex");
};
/*
* Copyright (C) 2011-2015 ArkCORE <http://www.arkania.net/>
*
* This program is free software; you can redistribute it and/or modify it
* under the terms of the GNU General Public License as published by the
* Free Software Foundation; either version 2 of the License, or (at your
* option) any later version.
*
* This program is distributed in the hope that it will be useful, but WITHOUT
* ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
* FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
* more details.
*
* You should have received a copy of the GNU General Public License along
* with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "uldaman.h"

class boss_galgann_firehammer : public CreatureScript
{
public:
    boss_galgann_firehammer() : CreatureScript("boss_galgann_firehammer") { }

    struct boss_galgann_firehammerAI : public BossAI
    {
        boss_galgann_firehammerAI(Creature* creature) : BossAI(creature, ENC_GALGANN_FIREHAMMER) { m_instance = creature->GetInstanceScript(); }

        InstanceScript* m_instance;
        EventMap m_events;
        uint32 m_phase;

        void Reset()
        {
            m_instance->SetData(ENC_GALGANN_FIREHAMMER, NOT_STARTED);
            m_events.Reset();
            m_phase = 0;
        }

        void EnterCombat(Unit* /*who*/)
        {
            m_instance->SetData(ENC_GALGANN_FIREHAMMER, IN_PROGRESS);
        }

        void JustDied(Unit* /*Killer*/)
        {
            m_instance->SetData(ENC_GALGANN_FIREHAMMER, DONE);
        }

        void UpdateAI(uint32 uiDiff)
        {
            if (!UpdateVictim())
                return;
            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return GetUldamanAI<boss_galgann_firehammerAI>(creature);
    }
};

void AddSC_boss_galgann_firehammer()
{
    new boss_galgann_firehammer();
}

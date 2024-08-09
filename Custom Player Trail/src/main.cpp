#include <Geode/geode.hpp>
#include <Geode/cocos/include/ccTypes.h>
#include <Geode/loader/Mod.hpp>
#include <Geode/modify/CCMotionStreak.hpp>
#include <Geode/modify/PlayLayer.hpp>
#include <Geode/modify/PlayerObject.hpp>
#include "color/colorConversion.cpp"

using namespace geode::prelude;

class $modify(PlayLayer) {
	void postUpdate(float p0) {
    PlayLayer::postUpdate(p0);

		bool enableRainbow = Mod::get()->getSettingValue<bool>("enable-rainbow");
		bool customColor = Mod::get()->getSettingValue<bool>("enable-custom-color");
		bool noTrailInWave = Mod::get()->getSettingValue<bool>("disable-trail-in-wave");
		bool disableTrail = Mod::get()->getSettingValue<bool>("disable-trail");

		float speed = Mod::get()->getSettingValue<double>("speed");
		float offset = Mod::get()->getSettingValue<double>("offset");
    float saturation = Mod::get()->getSettingValue<double>("saturation");
		float value = Mod::get()->getSettingValue<double>("brightness");
		float invertP2Rainbow = Mod::get()->getSettingValue<bool>("invert-player-2");

		if (!disableTrail) {
			if (enableRainbow && !customColor) {
				auto rainbowColor_1 = getRGB(1, saturation, value);
				auto rainbowColor_2 = getRGB(180, saturation, value);

				if (hue_base >= 360) {
					hue_base = 0;
				} else {
					hue_base += speed / 10;
				}

				if (invertP2Rainbow) {
					m_player1->m_regularTrail->setColor(rainbowColor_1);
					m_player2->m_regularTrail->setColor(rainbowColor_2);
				} else {
					m_player1->m_regularTrail->setColor(rainbowColor_1);
					m_player2->m_regularTrail->setColor(rainbowColor_1);
				}
			}

			if (customColor && !enableRainbow) {
				cocos2d::ccColor3B colorP1 = Mod::get()->getSettingValue<cocos2d::ccColor3B>("color-P1");
				cocos2d::ccColor3B colorP2 = Mod::get()->getSettingValue<cocos2d::ccColor3B>("color-P2");

				m_player1->m_regularTrail->setColor(colorP1);
				m_player2->m_regularTrail->setColor(colorP2);
			}

			if (m_player1->m_isDart && noTrailInWave) {
				m_player1->m_regularTrail->setVisible(false);
			} else if (!m_player1->m_isDart) {
				m_player1->m_regularTrail->setVisible(true);
			}

			if (m_player2->m_isDart && noTrailInWave) {
				m_player2->m_regularTrail->setVisible(false);
			} else if (!m_player2->m_isDart) {
				m_player2->m_regularTrail->setVisible(true);
			}

		} else{
			m_player1->m_regularTrail->setVisible(false);
      m_player2->m_regularTrail->setVisible(false);
		}
	}
};
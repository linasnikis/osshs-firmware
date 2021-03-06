/*
 * MIT License
 *
 * Copyright (c) 2019 Linas Nikiperavicius
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef OSSHS_PWM_EVENT_HPP
#define OSSHS_PWM_EVENT_HPP

#include <osshs/events/event_registrar.hpp>

namespace osshs
{
	namespace events
	{
		enum class PwmEvent : uint16_t
		{
			BASE = 0x02 << 8,

			REQUEST_STATUS,
			STATUS_READY,

			ENABLE,
			DISABLE,

			REQUEST_CHANNEL,
			CHANNEL_READY,

			UPDATE_CHANNEL,

			REQUEST_RGBW_CHANNEL,
			RGBW_CHANNEL_READY,

			UPDATE_RGBW_CHANNEL,

			UPDATE_SUCCESS,
			ERROR
		};

		enum class PwmStatus : uint8_t
		{
			ENABLED,
			DISABLED
		};

		enum class PwmError : uint8_t
		{
			CHANNEL_OUT_OF_BOUNDS,
			VALUE_OUT_OF_BOUNDS
		};

		typedef struct PwmRgbwValue
		{
			uint16_t red;
			uint16_t green;
			uint16_t blue;
			uint16_t white;

			PwmRgbwValue()
			{
				this->red = 0xfff;
				this->green = 0xfff;
				this->blue = 0xfff;
				this->white = 0xfff;
			}

			PwmRgbwValue(uint16_t red, uint16_t green, uint16_t blue, uint16_t white)
			{
				this->red = red;
				this->green = green;
				this->blue = blue;
				this->white = white;
			}
		} PwmRgbwValue;

		class PwmRequestStatusEvent : public EventRegistrar<PwmRequestStatusEvent>
		{
		public:
			static constexpr uint16_t EVENT_LENGTH = 6;
			static constexpr uint16_t TYPE = static_cast<uint16_t> (PwmEvent::REQUEST_STATUS);

			PwmRequestStatusEvent(std::unique_ptr<const uint8_t[]> data, EventCallback callback = nullptr);

			PwmRequestStatusEvent(uint16_t causeId = Event::CAUSE_ID_GENERATE, EventCallback callback = nullptr)
				: EventRegistrar<PwmRequestStatusEvent>(causeId, callback)
			{
			}

			std::unique_ptr<const uint8_t[]>
			serialize() const;
		};

		class PwmStatusReadyEvent : public EventRegistrar<PwmStatusReadyEvent>
		{
		public:
			static constexpr uint16_t EVENT_LENGTH = 7;
			static constexpr uint16_t TYPE = static_cast<uint16_t> (PwmEvent::STATUS_READY);

			PwmStatusReadyEvent(std::unique_ptr<const uint8_t[]> data, EventCallback callback = nullptr);

			PwmStatusReadyEvent(PwmStatus status, uint16_t causeId = Event::CAUSE_ID_GENERATE, EventCallback callback = nullptr)
				: EventRegistrar<PwmStatusReadyEvent>(causeId, callback), status(status)
			{
			}

			PwmStatus
			getStatus() const;

			std::unique_ptr<const uint8_t[]>
			serialize() const;
		private:
			PwmStatus status;
		};

		class PwmEnableEvent : public EventRegistrar<PwmEnableEvent>
		{
		public:
			static constexpr uint16_t EVENT_LENGTH = 6;
			static constexpr uint16_t TYPE = static_cast<uint16_t> (PwmEvent::ENABLE);

			PwmEnableEvent(std::unique_ptr<const uint8_t[]> data, EventCallback callback = nullptr);

			PwmEnableEvent(uint16_t causeId = Event::CAUSE_ID_GENERATE, EventCallback callback = nullptr)
				: EventRegistrar<PwmEnableEvent>(causeId, callback)
			{
			}

			std::unique_ptr<const uint8_t[]>
			serialize() const;
		};

		class PwmDisableEvent : public EventRegistrar<PwmDisableEvent>
		{
		public:
			static constexpr uint16_t EVENT_LENGTH = 6;
			static constexpr uint16_t TYPE = static_cast<uint16_t> (PwmEvent::DISABLE);

			PwmDisableEvent(std::unique_ptr<const uint8_t[]> data, EventCallback callback = nullptr);

			PwmDisableEvent(uint16_t causeId = Event::CAUSE_ID_GENERATE, EventCallback callback = nullptr)
				: EventRegistrar<PwmDisableEvent>(causeId, callback)
			{
			}

			std::unique_ptr<const uint8_t[]>
			serialize() const;
		};

		class PwmRequestChannelEvent : public EventRegistrar<PwmRequestChannelEvent>
		{
		public:
			static constexpr uint16_t EVENT_LENGTH = 8;
			static constexpr uint16_t TYPE = static_cast<uint16_t> (PwmEvent::REQUEST_CHANNEL);

			PwmRequestChannelEvent(std::unique_ptr<const uint8_t[]> data, EventCallback callback = nullptr);

			PwmRequestChannelEvent(uint16_t channel, uint16_t causeId = Event::CAUSE_ID_GENERATE, EventCallback callback = nullptr)
				: EventRegistrar<PwmRequestChannelEvent>(causeId, callback), channel(channel)
			{
			}

			uint16_t
			getChannel() const;

			std::unique_ptr<const uint8_t[]>
			serialize() const;
		private:
			uint16_t channel;
		};

		class PwmChannelReadyEvent : public EventRegistrar<PwmChannelReadyEvent>
		{
		public:
			static constexpr uint16_t EVENT_LENGTH = 10;
			static constexpr uint16_t TYPE = static_cast<uint16_t> (PwmEvent::CHANNEL_READY);

			PwmChannelReadyEvent(std::unique_ptr<const uint8_t[]> data, EventCallback callback = nullptr);

			PwmChannelReadyEvent(uint16_t channel, uint16_t value, uint16_t causeId = Event::CAUSE_ID_GENERATE, EventCallback callback = nullptr)
				: EventRegistrar<PwmChannelReadyEvent>(causeId, callback), channel(channel), value(value)
			{
			}

			uint16_t
			getChannel() const;

			uint16_t
			getValue() const;

			std::unique_ptr<const uint8_t[]>
			serialize() const;
		private:
			uint16_t channel;
			uint16_t value;
		};

		class PwmUpdateChannelEvent : public EventRegistrar<PwmUpdateChannelEvent>
		{
		public:
			static constexpr uint16_t EVENT_LENGTH = 10;
			static constexpr uint16_t TYPE = static_cast<uint16_t> (PwmEvent::UPDATE_CHANNEL);

			PwmUpdateChannelEvent(std::unique_ptr<const uint8_t[]> data, EventCallback callback = nullptr);

			PwmUpdateChannelEvent(uint16_t channel, uint16_t value, uint16_t causeId = Event::CAUSE_ID_GENERATE, EventCallback callback = nullptr)
				: EventRegistrar<PwmUpdateChannelEvent>(causeId, callback), channel(channel), value(value)
			{
			}

			uint16_t
			getChannel() const;

			uint16_t
			getValue() const;

			std::unique_ptr<const uint8_t[]>
			serialize() const;
		private:
			uint16_t channel;
			uint16_t value;
		};

		class PwmRequestRgbwChannelEvent : public EventRegistrar<PwmRequestRgbwChannelEvent>
		{
		public:
			static constexpr uint16_t EVENT_LENGTH = 8;
			static constexpr uint16_t TYPE = static_cast<uint16_t> (PwmEvent::REQUEST_RGBW_CHANNEL);

			PwmRequestRgbwChannelEvent(std::unique_ptr<const uint8_t[]> data, EventCallback callback = nullptr);

			PwmRequestRgbwChannelEvent(uint16_t channel, uint16_t causeId = Event::CAUSE_ID_GENERATE, EventCallback callback = nullptr)
				: EventRegistrar<PwmRequestRgbwChannelEvent>(causeId, callback), channel(channel)
			{
			}

			uint16_t
			getChannel() const;

			std::unique_ptr<const uint8_t[]>
			serialize() const;
		private:
			uint16_t channel;
		};

		class PwmRgbwChannelReadyEvent : public EventRegistrar<PwmRgbwChannelReadyEvent>
		{
		public:
			static constexpr uint16_t EVENT_LENGTH = 16;
			static constexpr uint16_t TYPE = static_cast<uint16_t> (PwmEvent::RGBW_CHANNEL_READY);

			PwmRgbwChannelReadyEvent(std::unique_ptr<const uint8_t[]> data, EventCallback callback = nullptr);

			PwmRgbwChannelReadyEvent(uint16_t channel, PwmRgbwValue value, uint16_t causeId = Event::CAUSE_ID_GENERATE, EventCallback callback = nullptr)
				: EventRegistrar<PwmRgbwChannelReadyEvent>(causeId, callback), channel(channel), value(value)
			{
			}

			uint16_t
			getChannel() const;

			PwmRgbwValue
			getValue() const;

			std::unique_ptr<const uint8_t[]>
			serialize() const;
		private:
			uint16_t channel;
			PwmRgbwValue value;
		};

		class PwmUpdateRgbwChannelEvent : public EventRegistrar<PwmUpdateRgbwChannelEvent>
		{
		public:
			static constexpr uint16_t EVENT_LENGTH = 16;
			static constexpr uint16_t TYPE = static_cast<uint16_t> (PwmEvent::UPDATE_RGBW_CHANNEL);

			PwmUpdateRgbwChannelEvent(std::unique_ptr<const uint8_t[]> data, EventCallback callback = nullptr);

			PwmUpdateRgbwChannelEvent(uint16_t channel, PwmRgbwValue value, uint16_t causeId = Event::CAUSE_ID_GENERATE, EventCallback callback = nullptr)
				: EventRegistrar<PwmUpdateRgbwChannelEvent>(causeId, callback), channel(channel), value(value)
			{
			}

			uint16_t
			getChannel() const;

			PwmRgbwValue
			getValue() const;

			std::unique_ptr<const uint8_t[]>
			serialize() const;
		private:
			uint16_t channel;
			PwmRgbwValue value;
		};

		class PwmUpdateSuccessEvent : public EventRegistrar<PwmUpdateSuccessEvent>
		{
		public:
			static constexpr uint16_t EVENT_LENGTH = 6;
			static constexpr uint16_t TYPE = static_cast<uint16_t> (PwmEvent::UPDATE_SUCCESS);

			PwmUpdateSuccessEvent(std::unique_ptr<const uint8_t[]> data, EventCallback callback = nullptr);

			PwmUpdateSuccessEvent(uint16_t causeId = Event::CAUSE_ID_GENERATE, EventCallback callback = nullptr)
				: EventRegistrar<PwmUpdateSuccessEvent>(causeId, callback)
			{
			}

			std::unique_ptr<const uint8_t[]>
			serialize() const;
		};

		class PwmErrorEvent : public EventRegistrar<PwmErrorEvent>
		{
		public:
			static constexpr uint16_t EVENT_LENGTH = 7;
			static constexpr uint16_t TYPE = static_cast<uint16_t> (PwmEvent::ERROR);

			PwmErrorEvent(std::unique_ptr<const uint8_t[]> data, EventCallback callback = nullptr);

			PwmErrorEvent(PwmError error, uint16_t causeId = Event::CAUSE_ID_GENERATE, EventCallback callback = nullptr)
				: EventRegistrar<PwmErrorEvent>(causeId, callback), error(error)
			{
			}

			PwmError
			getError() const;

			std::unique_ptr<const uint8_t[]>
			serialize() const;
		private:
			PwmError error;
		};
	}
}
#endif  // OSSHS_PWM_EVENT_HPP

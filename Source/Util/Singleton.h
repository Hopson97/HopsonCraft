#ifndef SINGLETON_H
#define SINGLETON_H

#include <memory>
#include <atomic>
#include <mutex>

// Class for accessing singleton instances.
template<typename T>
class Singleton {
public:
	// Get a (possibly new) copy of the singleton.
	static T& get() {
		if (m_init_done)
			return *get_underlying();
		std::unique_lock<std::mutex> lock(m_mutex);
		if (!m_init_done) {
			get_underlying() = std::make_unique<T>();
			m_init_done = true;
		}
		return *get_underlying();
	}

private:
	/* This implementation has the issue that the order of destruction of
	 * singletons is in inverse order to the construction.  Hence, be careful of
	 * using singletons in the destructors of other singletons.
	 */
	static std::unique_ptr<T>& get_underlying() {
		static std::unique_ptr<T> ptr;
		return ptr;
	}

	static std::atomic<bool> m_init_done;
	static std::mutex m_mutex;
};

template<typename T>
std::atomic<bool> Singleton<T>::m_init_done;
template<typename T>
std::mutex Singleton<T>::m_mutex;

#endif


/**
 * A simple thread pool API.
 * 
 * Tasks that wish to get run by the thread pool must implement the
 * java.lang.Runnable interface.
 */

import java.util.List;
import java.util.ArrayList;

public class ThreadPool {
	static int defaultSize = 3;
	private ThreadGroup Pool = new ThreadGroup("ThreadPool");
	private List<Runnable> queue = new ArrayList<Runnable>();

	/**
	 * Create a default size thread pool.
	 */
	public ThreadPool() {
		for (int i = 0; i < defaultSize; i++) {
			Thread thread = new Thread(Pool, new Execute());
			thread.start();
		}
	}

	/**
	 * Create a thread pool with a specified size.
	 * 
	 * @param int size The number of threads in the pool.
	 */
	public ThreadPool(int size) {
		for (int i = 0; i < size; i++) {
			Thread thread = new Thread(Pool, new Execute());
			thread.start();
		}
	}

	/**
	 * shut down the pool.
	 */
	public void shutdown() {
		Pool.interrupt();
	}

	/**
	 * Add work to the queue.
	 */
	public synchronized void add(Runnable task) {
		queue.add(task);
		notify();
	}

	public synchronized Runnable remove() throws InterruptedException {
		while (queue.isEmpty()) {
			try {
				wait();
			} catch (InterruptedException ie) {
				throw ie;
			}
		}

		return queue.remove(0);
	}

	class Execute implements Runnable {
		public void run() {
			while (!Thread.currentThread().isInterrupted()) {
				try {
					Runnable worker = remove();
					worker.run();
				} catch (InterruptedException ie) {
					Thread.currentThread().interrupt();
				}

			}
		}
	}
}

class SingleChain():
	def __init__(data, next_chain):
		self.next_chain = next_chain
		self.data = data



class Chain():
	def __init__(head=None):
		self.head = head


def init():
	return Chain()